#pragma once
class Surface
{
public:
	GLuint vao = assets.models.quad;
	Shader shader = assets.shaders.surfaceShader;
	Texture texture;

	Surface(Texture tex);
	void draw();
};

