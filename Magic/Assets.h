#pragma once

class Assets {
public:
	struct Shaders {
		Shader lampShader;
		Shader modelShader;
	} shaders;

	struct Models {
		Model* nanosuit = nullptr;
		Model* cube = nullptr;
		Model* plane = nullptr;
		Model* sphere = nullptr;
	} models;

	Assets();

	void loadAssets() {
		loadShaders();
		loadModels();
	}

	void clean() {
		delete(models.nanosuit);
		delete(models.cube);
		delete(models.plane);
		delete(models.sphere);
	}

private:
	void loadShaders();
	void loadModels();
};