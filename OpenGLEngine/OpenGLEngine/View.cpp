#include "View.h"

SDL_Window * View::screen;

mat4 View::projectionMatrix;

MPlayer * View::player;// = new MPlayer();

MCamera * View::camera;// = player->GetCamera();

void View::Initialise()
{
	screen = SDL_CreateWindow("Arch Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	
  SDL_GL_CreateContext(View::screen);

  player = new MPlayer();
	camera = player->GetCamera();

	projectionMatrix = glm::perspective(3.1416f / 2, SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 10000.f);
}
