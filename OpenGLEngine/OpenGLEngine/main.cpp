#define GLEW_STATIC
#include "SDL.h"
#include "ModelLibrary.h"
#include "Utility.h"
#include "ShaderLibrary.h"
#include "InputManager.h"
#include "Interface2D.h"
#include "SDL_ttf.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "SoundManager.h"
#include "Screen.h"
#include "MCamera.h"
#include <GL/glew.h>
#include "assimp/Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postProcess.h"
#include <chrono>
#include "RenderableObject.h"
#include "TextureLibrary.h"
#include "FrameBuffer.h"


// Important Resources:
// ... Basically everything you need to know Lazy Foo has you covered...
//
// Using modern openGL and SDL 
// http://lazyfoo.net/tutorials/SDL/51_SDL_and_modern_opengl/index.php
//
// For a complete reference:
// http://lazyfoo.net/tutorials/OpenGL/index.php
//


SDL_Window* screen;

//SkinnedMesh* mesh;

RenderableObject* pObject;

glm::mat4 projectionMatrix;

glm::vec3 camPos;
float yaw;
float pitch;
MCamera camera;


// initializes setting
void myinit();
void GameLoop();
bool HandleEvents();

void UpdatePlayer()
{
	const float TURN_SPEED = 0.3f;
	const float MOVE_SPEED = 0.5f;

	InputManager* im = InputManager::GetInputManager();

	//Rotation
	float originalYaw = camera.getYaw();
	float originalPitch = camera.getPitch();
	float deltaYaw = -im->MouseDeltaX() * TURN_SPEED;
	float deltaPitch = -im->MouseDeltaY() * TURN_SPEED;
	camera.SetYaw(originalYaw + deltaYaw);
	camera.SetPitch(originalPitch + deltaPitch);

	//Translation
	vec3 oldPos = camera.GetPosition();
	vec3 forward = camera.Forward();
	vec3 right = camera.Right();
	vec3 translation = vec3{ 0, 0, 0 };

	if (im->IsKeyDown(SDL_SCANCODE_W))
		translation += forward;
	if (im->IsKeyDown(SDL_SCANCODE_A))
		translation -= right;
	if (im->IsKeyDown(SDL_SCANCODE_S))
		translation -= forward;
	if (im->IsKeyDown(SDL_SCANCODE_D))
		translation += right;

	if (translation != vec3{ 0, 0, 0 })
	{
		//Normalize so you dont move faster diagonally
		translation = normalize(translation);

		translation *= MOVE_SPEED;

		if (im->IsKeyDown(SDL_SCANCODE_LSHIFT))
			translation *= 2;

		//Clamp Player to room

		vec3 newPos = oldPos;

		newPos.x += translation.x;
		newPos.y += translation.y;
		newPos.z += translation.z;
		camera.SetPosition(newPos);
	}
}

bool initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		getchar();
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		printf("SDL sound could not initialize! SDL Error: %s\n", SDL_GetError());
		getchar();
		return false;
	}
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
	screen = SDL_CreateWindow("Arch Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	SDL_GL_CreateContext(screen);

  SDL_GL_SetSwapInterval(-1);

	SDL_SetRelativeMouseMode(SDL_TRUE);

	return true;
}

int main(int argc, char **argv)
{
	initSDL();
	myinit();
	GameLoop();
	return(0);
}

void InitGlew()
{
	//Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();

	if (glewError != GLEW_OK)
	{
		printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
	}
}

void myinit()
{
	glClearColor(0, 0, 0, 1.f);

	InitGlew();

	TextureLibrary::GetInstance().initTextureLibrary();
	ShaderLibrary::getLib()->initShaderLibrary();
	SoundManager::GetSoundManager()->initSoundManager();
  FrameBuffer::Initialize();

	projectionMatrix = glm::perspective(3.1416f / 2, SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 10000.f);
  pObject = new RenderableObject("zombie", "bob.md5mesh");
}

bool HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		switch (event.type)
		{
		case SDL_QUIT:
			return false;
		case SDL_MOUSEMOTION:
			InputManager::GetInputManager()->PushEvent(MouseEvent(event.motion));
			break;
		case SDL_MOUSEBUTTONDOWN:
			InputManager::GetInputManager()->PushEvent(MouseEvent(event.button));
			break;
		case SDL_MOUSEBUTTONUP:
			InputManager::GetInputManager()->PushEvent(MouseEvent(event.button));
			break;
		}
	}
	return true;
}

bool Update()
{
	if (!HandleEvents())
		return false;

	InputManager::GetInputManager()->Update();

	if (InputManager::GetInputManager()->IsKeyDown(SDL_SCANCODE_ESCAPE))
		return false;

	UpdatePlayer();

	return true;
}

void Render()
{
  ShaderLibrary::getLib()->bindShader("skinning");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

  pObject->Render( glm::mat4(), camera.getViewMatrix(), projectionMatrix, FM_Fill, DS_Texture, 0, clock() / float(CLOCKS_PER_SEC));

	glFlush();
	SDL_GL_SwapWindow(screen);
}

void GameLoop()
{
	while (true)
	{
		if (!Update())
			break;
		Render();

	}
}