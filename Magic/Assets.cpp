#include "stdafx.h"
#include "Assets.h"

Assets::Assets()
{
}

void Assets::loadShaders()
{
	shaders.lampShader.load("shaders/v_lamp.glsl", "shaders/f_lamp.glsl");
	shaders.modelShader.load("shaders/v_model.glsl", "shaders/f_model.glsl");
}

void Assets::loadModels() {
	models.plane = new Model("data/models/plane/plane.obj");
	models.cube = new Model("data/models/cube/textured_cube.obj");
	models.sphere = new Model("data/models/orb/orb.obj");
	models.tree = new Model("data/models/tree/tree.obj");
	//models.nanosuit = new Model("data/models/nanosuit/nanosuit.obj");
}
