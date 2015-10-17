// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

//	Third party headers
#include <glew.h>
#include <glfw\glfw3.h>
#include <gl\GL.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//	Standard headers
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <tchar.h>

//	Local headers
#include "Shader.h"
#include "Drawing.h"
#include "Preferences.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
#include "Lighting.h"
#include "Entity.h"
#include "Assets.h"


// TODO: reference additional headers your program requires here
