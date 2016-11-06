#include "Screen.h"

SDL_Surface* screen;

SDL_Surface* GetScreenSurface()
{
	return screen;
}

void SetScreenSurface(SDL_Surface* Screen)
{
	screen = Screen;
}