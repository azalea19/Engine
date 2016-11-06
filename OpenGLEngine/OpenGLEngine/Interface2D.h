#ifndef Interface2D_h__
#define Interface2D_h__

#include "Types.h"

/**
* @file   2DInterface.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The methods used to render the 2D aspects of the game.
*
* The text rendering file uses SDL2's SDL_ttf and SDL_Image library to Blit on to an SDL surface.
* This surface is copied in to an OpenGL format where we can render it to the screen using an orthographic shader.
* 
* SDL_ttf's extension library and use is explained here in Lazy Foo's tutorial:
* http://lazyfoo.net/tutorials/SDL/16_true_type_fonts/index.php
* See this link for using an SDL surface as an OpenGL texture:
* http://www.sdltutorials.com/sdl-tip-sdl-surface-to-opengl-texture
*
*/


void drawImage(string filePath);


void drawText(int size, string filePath, string text, int xpos, int ypos, vec3 color = vec3(0, 0, 0));


static void breakOnGLError();

#endif 
