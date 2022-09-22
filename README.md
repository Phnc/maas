# Verificação de Modelos Comportamentais UML Como um Serviço Habilitando a Aplicação de Métodos Formais Ocultos

## Flow

![figura10](https://user-images.githubusercontent.com/36466228/191639951-40ae7321-9486-4c77-986e-eaf3e0ab1e46.png)

## Setup

1. Install Java version 8
2. Clone this repository
3. Build the jar file from the project
4. Run the application with the .jar generated

The application will run by default on port 8080

# :triangular_flag_on_post: Endpoints

### `/index - GET`. Returns an HTML page with the front-end built for this project.

### `/getDiagrams - POST`. Returns a JSON with the available diagrams in the submitted file.

This endpoint expects a file in the body of the request.

### `/validateAstahFile - POST`. Returns an Astah file with the counter-example, if it exists.

This endpoint expects a file in the body of the request. The query parameters passed to it are validationType (determinism or deadlock) and diagramName.
