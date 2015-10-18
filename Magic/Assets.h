#pragma once

class Assets {
public:
	struct CubeMaps {
		CubeMap lake;
	} cubemaps;

	struct Textures {
		Texture splash;
	}textures;

	struct Shaders {
		Shader surfaceShader; // Shader for quad/surface

		Shader lampShader;
		Shader modelShader;
		Shader outlineShader;
		Shader skyboxShader;
	} shaders;

	struct Models {
		GLuint quad; // VAO for quad surface
		GLuint box;  // VAO for box

		Model* nanosuit = nullptr;
		Model* cube = nullptr;
		Model* plane = nullptr;
		Model* sphere = nullptr;
		Model* tree = nullptr;
	} models;

	Assets();

	void loadAssets() {
		loadShaders();
		loadModels();
		loadTextures();
		loadCubeMaps();
	}

	void loadQuad();
	void loadCube();

	void clean() {
		delete(models.nanosuit);
		delete(models.cube);
		delete(models.plane);
		delete(models.sphere);
		delete(models.tree);
	}

private:
	void loadShaders();
	void loadModels();
	void loadTextures();
	void loadCubeMaps();
};