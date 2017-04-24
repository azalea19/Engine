#include "Screen.h"

static SDL_Surface* screen;
static int SCREEN_WIDTH = 1280;
static int SCREEN_HEIGHT = 720;
static float NEAR_PLANE = 0.01f;
static float FAR_PLANE = 10000.0f;


SDL_Surface* GetScreenSurface()
{
	return screen;
}

void SetScreenSurface(SDL_Surface* Screen)
{
	screen = Screen;
}

void SetScreenDimensions(vec2i const& dimensions)
{
  SCREEN_WIDTH = dimensions.x;
  SCREEN_HEIGHT = dimensions.y;
}

void SetNearPlane(float nearPlane)
{
  NEAR_PLANE = nearPlane;
}

float GetNearPlane()
{
  return NEAR_PLANE;
}

float GetFarPlane()
{
  return FAR_PLANE;
}

void SetFarPlane(float farPlane)
{
  FAR_PLANE = farPlane;
}

vec2i const& GetScreenDimensions()
{
  return vec2i(SCREEN_WIDTH, SCREEN_HEIGHT);
}