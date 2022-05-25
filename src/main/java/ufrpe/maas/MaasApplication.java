package ufrpe.maas;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.ModelAndView;

import javax.swing.text.html.HTML;
import java.io.File;

@SpringBootApplication
@RestController
public class MaasApplication {

	public static void main(String[] args) {
		SpringApplication.run(MaasApplication.class, args);
	}
	@GetMapping("/hello")
	public String hello(@RequestParam(value = "name", defaultValue = "World") String name) {
		return String.format("Hello %s!", name);
	}

	@RequestMapping("/index")
	public String index() {
		return "uploader.html";
	}

	@PostMapping("/upload")
	public ResponseEntity<?> handleFileUpload(@RequestParam("file")MultipartFile file){
		String fileName = file.getOriginalFilename();
		try{
			file.transferTo(new File("C:\\upload\\" + fileName));
		} catch (Exception e){
			return  ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).build();
		}
		return ResponseEntity.ok("File uploaded successfully");
	}
}
