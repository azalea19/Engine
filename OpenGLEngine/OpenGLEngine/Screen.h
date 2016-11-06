#ifndef SCREEN_H__
#define SCREEN_H__

/**
* @file   Screen.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The screen file.
*
* The screen file contains constants and functions relating to the screen.
*/


struct SDL_Surface;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const float NEAR_PLANE = 6.0f;
const float FAR_PLANE = 10000.0f;

SDL_Surface* GetScreenSurface();

void SetScreenSurface(SDL_Surface* screen);

#endif