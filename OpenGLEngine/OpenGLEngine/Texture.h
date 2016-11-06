#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>

/**
* @file   Texture.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The function to load textures.
*
* The texture file has two options for loading textures. The loadBMP() which can only load a bmp file 
* and the loadImage() method which uses SDL2's IMG_Load internally. The loadImage() method
* can handle PNG's, TGA's, JPEG's, BMP's. See SDL2's IMG_Load for a full list of supported file types.
* 
* See SDL documentation for SDL_image API information:
* https://www.libsdl.org/projects/SDL_image/docs/SDL_image_5.html#SEC5
*
*/


GLuint loadBMP(const char * imagepath);

GLuint loadImage(const char * imagepath);

#endif