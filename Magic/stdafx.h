// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <glew\glew.h>
#include <sdl\SDL.h>
#include <sdl\SDL_image.h>
#include <sdl\SDL_ttf.h>
#include <sdl\SDL_opengl.h>
#include <Box2D\Box2D.h>

#include "Shader.h"

#include <stdio.h>
#include <iostream>
#include <tchar.h>


#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}



// TODO: reference additional headers your program requires here
