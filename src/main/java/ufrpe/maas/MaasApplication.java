package ufrpe.maas;

import JP.co.esm.caddies.tools.judedoc.Res;
import com.change_vision.jude.api.inf.AstahAPI;
import com.change_vision.jude.api.inf.exception.ProjectNotFoundException;
import com.change_vision.jude.api.inf.model.IActivityDiagram;
import com.change_vision.jude.api.inf.model.INamedElement;
import com.change_vision.jude.api.inf.model.IStateMachineDiagram;
import com.change_vision.jude.api.inf.project.ModelFinder;
import com.change_vision.jude.api.inf.project.ProjectAccessor;
import com.ref.ActivityController;
import com.ref.StateMachineController;
import com.ref.astah.statemachine.adapter.StateMachine;
import com.ref.astah.statemachine.adapter.StateMachineDiagram;
import com.ref.ui.CheckingProgressBar;
import io.swagger.annotations.ApiParam;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.boot.web.servlet.error.ErrorController;
import org.springframework.context.ConfigurableApplicationContext;
import org.springframework.core.io.ByteArrayResource;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import ufrpe.maas.utils.StringResponse;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@SpringBootApplication
@RestController
public class MaasApplication {

	private final static String PATH = "/error";
	public static void main(String[] args) {
		//SpringApplication.run(MaasApplication.class, args);
		SpringApplicationBuilder builder = new SpringApplicationBuilder(MaasApplication.class);

		builder.headless(false);

		ConfigurableApplicationContext context = builder.run(args);
	}

	@GetMapping("/index")
	public String index() {
		return "uploader.html";
	}

	public static INamedElement[] findElements(ProjectAccessor projectAccessor) throws ProjectNotFoundException {
		INamedElement[] foundElements = projectAccessor.findElements(new ModelFinder() {
			public boolean isTarget(INamedElement namedElement) {
				return namedElement instanceof IActivityDiagram || namedElement instanceof IStateMachineDiagram;
			}
		});
		return foundElements;
	}

	public String saveFile(MultipartFile file){
		String basePath ="C:\\upload\\";
		String fileName = file.getOriginalFilename();

		try {
			String finalPath = basePath + fileName;

			file.transferTo(new File(finalPath));

			return finalPath;
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}

	@PostMapping("/getDiagrams")
	public ResponseEntity<List<StringResponse>> getDiagrams(@RequestParam("file") MultipartFile file){
		try {
			String filePath = saveFile(file);

			ProjectAccessor projectAccessor = AstahAPI.getAstahAPI().getProjectAccessor();
			projectAccessor.open(filePath);

			INamedElement[] findElements = findElements(projectAccessor);
			List<StringResponse> names = new ArrayList<>();

			for (INamedElement element : findElements){
				names.add(new StringResponse(element.getName()));
			}
			projectAccessor.close();
			return ResponseEntity.ok(names);
		}
		catch (Exception ex){
			return  null;
		}
	}

	@PostMapping("/validateAstahFile")
	public ResponseEntity<?> validateAstah(@ApiParam(value="File", required=true) @RequestPart MultipartFile file, @RequestParam("validationType") String validationType, @RequestParam("diagramName") String diagramName){
		try {


			String filePath = saveFile(file);

			ProjectAccessor projectAccessor = AstahAPI.getAstahAPI().getProjectAccessor();
			projectAccessor.open(filePath);

			INamedElement[] findElements = findElements(projectAccessor);
			INamedElement diagram = Arrays.stream(findElements).filter(e -> e.getName().equals(diagramName)).findFirst().orElse(null);

			boolean isActivity = diagram instanceof IActivityDiagram;
			boolean isStateMachine = diagram instanceof IStateMachineDiagram;

			CheckingProgressBar bar = new CheckingProgressBar();

			if(isActivity){
				ActivityController.VerificationType type = validationType.equals("determinism") ? ActivityController.VerificationType.DETERMINISM : ActivityController.VerificationType.DEADLOCK;

				IActivityDiagram ad = (IActivityDiagram) diagram;

				ActivityController ac = ActivityController.getInstance();


				ac.AstahInvocation(ad, type, bar);


			}

			else if (isStateMachine){
				StateMachineController.VerificationType type = validationType.equals("determinism") ? StateMachineController.VerificationType.DETERMINISM : StateMachineController.VerificationType.DEADLOCK;

				IStateMachineDiagram smDiagram = (IStateMachineDiagram) diagram;

				StateMachineController smc = StateMachineController.getInstance();

				smc.AstahInvocation(smDiagram, type, bar);

			}
			bar.dispose();
			projectAccessor.save();
			projectAccessor.close();

			Path path = Paths.get(filePath);
			ByteArrayResource resource = new ByteArrayResource(Files.readAllBytes(path));

			HttpHeaders headers = new HttpHeaders();

			String headerValue = "attachment; "+"filename="+file.getOriginalFilename()+".asta";

			headers.add(HttpHeaders.CONTENT_DISPOSITION, headerValue);

			return ResponseEntity.ok()
					.headers(headers)
					.contentType(MediaType.APPLICATION_OCTET_STREAM)
					.body(resource);
		}
		catch (Exception ex){
			return  ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
		}
	}

}
