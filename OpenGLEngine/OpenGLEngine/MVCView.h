#pragma once
#include "SDL.h"
#include "Utility.h"
#include "MCamera.h"
#include "MPlayer.h"
#include "time.h"
#include "ModelLibrary.h"
#include "Utility.h"
#include "Screen.h"
#include <iostream>
#include "MMath.h"


class MVCView
{
public:
	static SDL_Window *screen;
	static MCamera *camera; // Placeholder. This should be pointer(s) to player(s) camera
	static mat4 projectionMatrix;
	static MPlayer *player; // Move somewhere else. Model

	static void Initialise();

};

