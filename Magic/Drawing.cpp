#include "stdafx.h"
#include "Drawing.h"

class Camera;
extern Camera camera;

//	Shaders
Shader flatShader;
Shader lampShader;

//	Meshes
GLuint box = 0;
GLuint square = 0;
GLuint lamp = 0;

//	Textures
GLuint crate_diff = 0;
GLuint crate_spec = 0;
GLuint grass = 0;

Lighting::LightScene lightScene;

GLuint Drawing::loadTextureFile(std::string texturePath) {
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height;
	unsigned char* image = SOIL_load_image(texturePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	if (image == nullptr) {
		std::cerr << "Failed to load image: " + texturePath;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);

	return tex;
}

GLuint loadLamp() {
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f, 
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f, -0.5f, 
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
							
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
							
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
							
		0.5f,  0.5f,  0.5f, 
		0.5f,  0.5f, -0.5f, 
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 
							
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f,  0.5f, 
		0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
							
		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};


	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	return vao;
}

GLuint Drawing::loadBox() {
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,0.0f, 0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f, 0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f, 0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f, 0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f, 0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f, 0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,-1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,-1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,-1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,-1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,-1.0f, 0.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	return vao;
}

GLuint Drawing::loadSquare() {
	float vertices[] = {
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f
	};

	GLuint elements[] = {
		0,1,2,
		2,3,0,
	};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));


	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	return vao;
}

void Drawing::loadTextures() {
	crate_diff = loadTextureFile("data/textures/box_diffuse.png");
	crate_spec = loadTextureFile("data/textures/box_spec.png");
	grass = loadTextureFile("data/textures/grass.jpg");
}

void Drawing::loadMeshes() {
	box = loadBox();
	square = loadSquare();
	lamp = loadLamp();
}

void Drawing::loadShaders() {
	flatShader.load("shaders/v_default.glsl", "shaders/f_default.glsl");
	lampShader.load("shaders/v_lamp.glsl", "shaders/f_lamp.glsl");
}

void setLightScene(Lighting::LightScene &lightScene) {

	//	Set directional light
	float luminosity = 0.0f;
	Lighting::Colour colour;
	colour.ambient = glm::vec3(luminosity);
	colour.diffuse = glm::vec3(luminosity);
	colour.specular = glm::vec3(1.0f, 1.0f, 1.0f) * luminosity;

	glm::vec3 direction(-1.0f, -0.25f, -1.0f);

	lightScene.setDirectionalLight(direction, colour);

	//	Set 4 point lights
	Lighting::Attenuation attenuation;
	attenuation.constant = 1.0f;
	attenuation.linear = 0.09f;
	attenuation.quadratic = 0.032f;

	glm::vec3 pointColour;

	pointColour = glm::vec3(1.0f,1.0f, 1.0f);
	colour.ambient = pointColour * 0.2f;
	colour.diffuse = pointColour;
	colour.specular = pointColour;
	lightScene.addPointLight(glm::vec3(14.0f, 2.0f, 5.0f), colour, attenuation, 0);
}

void Drawing::init(Camera &cam) {
	camera = cam;

	loadShaders();
	loadMeshes();
	loadTextures();

	setLightScene(lightScene);
	flatShader.Use();
	lightScene.uploadUniforms(flatShader.id);
}

void Drawing::drawTexture(GLuint diffuse, GLuint specular, GLuint mesh, glm::vec3 &position, glm::vec3 &size, glm::vec4 &rotation) {
	glBindVertexArray(mesh);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuse);
	glUniform1i(glGetUniformLocation(flatShader.id, "material.diffuse"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specular);
	glUniform1i(glGetUniformLocation(flatShader.id, "material.specular"), 1);


	glm::mat4 model;
	model = glm::translate(model, position);
	model = glm::rotate(model, rotation.w, glm::vec3(rotation.x, rotation.y, rotation.z));
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));

	glm::mat4 view;
	view = glm::lookAt(camera.cameraPos, camera.cameraPos+camera.cameraFront, camera.cameraUp);

	glm::mat4 proj;
	proj = glm::perspective(camera.fov, (float)Preferences::SCREEN_WIDTH / (float)Preferences::SCREEN_HEIGHT, 0.1f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(flatShader.id, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(flatShader.id, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(flatShader.id, "projection"), 1, GL_FALSE, glm::value_ptr(proj));
	

	GLint matSpecularLoc = glGetUniformLocation(flatShader.id, "material.specular");
	GLint matShineLoc = glGetUniformLocation(flatShader.id, "material.shininess");

	glUniform3f(matSpecularLoc, 0.5f, 0.5f, 0.5f);
	glUniform1f(matShineLoc, 32.0f);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Drawing::drawGrid() {
	glBindVertexArray(square);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, grass);
	glUniform1i(glGetUniformLocation(flatShader.id, "material.diffuse"), 0);

	glm::mat4 view;
	view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);
	glm::mat4 proj;
	proj = glm::perspective(camera.fov, (float)Preferences::SCREEN_WIDTH / (float)Preferences::SCREEN_HEIGHT, 0.1f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(flatShader.id, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(flatShader.id, "projection"), 1, GL_FALSE, glm::value_ptr(proj));

	GLint matSpecularLoc = glGetUniformLocation(flatShader.id, "material.specular");
	GLint matShineLoc = glGetUniformLocation(flatShader.id, "material.shininess");

	glUniform3f(matSpecularLoc, 0.1f, 0.1f, 0.1f);
	glUniform1f(matShineLoc, 32.0f);

	float size = 5;
	float scale = 5;
	for (float x = 0; x < scale*size; x+=scale) {
		for (float z = 0; z < scale*size; z+=scale) {
			glm::mat4 model;
			model = glm::translate(model, glm::vec3(2*x, 0.0f, 2*z));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(scale, scale, scale));
			glUniformMatrix4fv(glGetUniformLocation(flatShader.id, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
	glBindVertexArray(0);
}

void Drawing::drawLamp(glm::vec3 position) {
	glBindVertexArray(lamp);

	glm::mat4 model;
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	glm::mat4 view;
	view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);
	glm::mat4 proj;
	proj = glm::perspective(camera.fov, (float)Preferences::SCREEN_WIDTH / (float)Preferences::SCREEN_HEIGHT, 0.1f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(lampShader.id, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(lampShader.id, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(lampShader.id, "projection"), 1, GL_FALSE, glm::value_ptr(proj));

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Drawing::render() {
	using namespace Drawing;
	
	flatShader.Use();
	glUniform3f(glGetUniformLocation(flatShader.id, "cameraPos"), camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);

	//  Grid
	drawGrid();
	//	Boxes
	for (float i = 0; i < 10; i++)
		drawTexture(crate_diff, crate_spec, box, glm::vec3(3.0f * i + 5.0f, glm::sin(2 * glfwGetTime() + (5 * i)) + 2.0f, 20.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f,0.1f * i * glfwGetTime()));

	lampShader.Use();
	drawLamp(lightScene.pointLights[0].position);
	glUseProgram(0);
}

void Drawing::cleanup()
{
	//lightScene->cleanup();
	//delete(lightScene);
}

