#ifndef SCREEN_H__
#define SCREEN_H__

#include "Types.h"

/**
* @file   Screen.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief  The screen file.
*
* The screen file contains constants and functions relating to the screen.
*/


struct SDL_Surface;


void SetScreenDimensions(vec2i const& dimensions);

vec2i const& GetScreenDimensions();

void SetNearPlane(float nearPlane);

void SetFarPlane(float farPlane);

float GetNearPlane();

float GetFarPlane();


SDL_Surface* GetScreenSurface();

void SetScreenSurface(SDL_Surface* screen);

#endif