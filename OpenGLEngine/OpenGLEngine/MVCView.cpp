#include "MVCView.h"

SDL_Window * MVCView::screen;

mat4 MVCView::projectionMatrix;

MPlayer * MVCView::player;// = new MPlayer();

MCamera * MVCView::camera;// = player->GetCamera();

void MVCView::Initialise()
{
	screen = SDL_CreateWindow("Arch Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	player = new MPlayer();
	camera = player->GetCamera();

	projectionMatrix = glm::perspective(3.1416f / 2, SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 10000.f);
}
