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
#include <GL/glew.h>
#include "SceneGraph.h"
#include "ModelNode.h"
#include "BasicTextureNode.h"
#include "BasicMeshNode.h"
#include "HeightMap.h"
#include "MeshGenerator.h"
#include "MeshLibrary.h"
#include "assimp/Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postProcess.h"


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

SceneGraph* sceneGraph;


// initializes setting
void myinit();
void GameLoop();
bool HandleEvents();

ModelNode* CreateModelNode(string meshName)
{
	BasicMeshNode* mesh = new BasicMeshNode(sceneGraph, meshName);
	ModelNode* modelNode = new ModelNode(sceneGraph);
	modelNode->SetMeshNode(mesh);
	modelNode->SetTextureNode(nullptr);
	return modelNode;
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
	Assimp::Importer floja;
	const aiScene* soldier = floja.ReadFile("soldier.dae", aiProcess_Triangulate);
	soldier->mMeshes[0]->
	glClearColor(0, 0, 0, 1.f);

	InitGlew();

	ShaderLibrary::getLib()->initShaderLibrary();
	ModelLibrary::getLib()->initModelLibrary();
	SoundManager::GetSoundManager()->initSoundManager();



	WaveSampleArgs margs = { 0, 20, 50 };
	float* heightMap = CreateHeightMap(512, 512, XWaveSample, &margs);
	MeshData* meshData = CreateMeshFromHeightMap(512, 512, heightMap);
	MeshLibrary::GetInstance().AddMesh("XWaveMesh", *meshData);

	free(heightMap);
	delete meshData;




	sceneGraph = new SceneGraph(90, SCREEN_WIDTH, SCREEN_HEIGHT, 0.1f, 1000.f);
	sceneGraph->SetRoot(CreateModelNode("XWaveMesh"));


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


	return true;
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	sceneGraph->Render();
	// clear buffers 

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