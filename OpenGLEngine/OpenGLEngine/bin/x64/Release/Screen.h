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
/// <summary>
/// Set screen dimension.
/// </summary>
/// <param name="dimensions">Dimensions.</param>
void SetScreenDimensions(vec2i const& dimensions);

/// <summary>
/// Gets screen dimension.
/// </summary>
/// <returns></returns>
vec2i const& GetScreenDimensions();

/// <summary>
/// Set near plane.
/// </summary>
/// <param name="nearPlane">Near plane.</param>
void SetNearPlane(float nearPlane);

/// <summary>
/// Set far plane.
/// </summary>
/// <param name="farPlane">Far plane.</param>
void SetFarPlane(float farPlane);
/// <summary>
/// Gets near plane.
/// </summary>
/// <returns></returns>
float GetNearPlane();
/// <summary>
/// Gets far plane.
/// </summary>
/// <returns></returns>
float GetFarPlane();


SDL_Surface* GetScreenSurface();

void SetScreenSurface(SDL_Surface* screen);

#endif