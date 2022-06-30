package ufrpe.maas;

import com.change_vision.jude.api.inf.AstahAPI;
import com.change_vision.jude.api.inf.exception.ProjectNotFoundException;
import com.change_vision.jude.api.inf.model.IActivityDiagram;
import com.change_vision.jude.api.inf.model.INamedElement;
import com.change_vision.jude.api.inf.project.ModelFinder;
import com.change_vision.jude.api.inf.project.ProjectAccessor;
import com.ref.ActivityController;
import com.ref.ui.CheckingProgressBar;
import com.sun.glass.ui.Application;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.context.ConfigurableApplicationContext;
import org.springframework.core.io.ByteArrayResource;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.ModelAndView;

import javax.swing.text.html.HTML;
import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

@SpringBootApplication
@RestController
public class MaasApplication {

	public static void main(String[] args) {
		//SpringApplication.run(MaasApplication.class, args);
		SpringApplicationBuilder builder = new SpringApplicationBuilder(MaasApplication.class);

		builder.headless(false);

		ConfigurableApplicationContext context = builder.run(args);
	}
	@GetMapping("/hello")
	public String hello(@RequestParam(value = "name", defaultValue = "World") String name) {
		return String.format("Hello %s!", name);
	}

	@RequestMapping("/index")
	public String index() {
		return "uploader.html";
	}

	public static INamedElement[] findElements(ProjectAccessor projectAccessor) throws ProjectNotFoundException {
		INamedElement[] foundElements = projectAccessor.findElements(new ModelFinder() {
			public boolean isTarget(INamedElement namedElement) {
				return namedElement instanceof IActivityDiagram;
			}
		});
		return foundElements;
	}

	@PostMapping("/upload")
	public ResponseEntity<?> handleFileUpload(@RequestParam("file")MultipartFile file){
		String fileName = file.getOriginalFilename();
		try{
			file.transferTo(new File("C:\\upload\\" + fileName));

			ProjectAccessor projectAccessor = AstahAPI.getAstahAPI().getProjectAccessor();
			projectAccessor.open("C:\\upload\\" + fileName);

			INamedElement[] findElements = findElements(projectAccessor);

			IActivityDiagram ad = (IActivityDiagram) findElements[0];

			ActivityController ac = ActivityController.getInstance();
			CheckingProgressBar bar = new CheckingProgressBar();
			ac.AstahInvocation(ad, ActivityController.VerificationType.DEADLOCK, bar);

			bar.dispose();

			projectAccessor.save();
			projectAccessor.close();

			Path path = Paths.get("C:\\upload\\" + fileName);
			ByteArrayResource resource = new ByteArrayResource(Files.readAllBytes(path));

			HttpHeaders headers = new HttpHeaders(); headers.add(HttpHeaders.CONTENT_DISPOSITION, "attachment; filename=file.astah");

			return ResponseEntity.ok()
					.headers(headers)
					.contentType(MediaType.APPLICATION_OCTET_STREAM)
					.body(resource);

		} catch (Exception e){
			return  ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
		}
	}
}
