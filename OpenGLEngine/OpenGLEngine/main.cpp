#define GLEW_STATIC
#include "SDL.h"
#include "time.h"
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
#include "SceneDecomposeEffect.h"
#include "Texture.h"
#include "LuaManager.h"
#include <iostream>
#include "DepthThresholdEffect.h"
#include "GodRaysEffect.h"
#include "BloomEffect.h"
#include "FXAAEffect.h"
#include "ObjectInstance.h"
#include "MMath.h"
#include "ForestTerrain.h"
#include "MultiplicativeBlendEffect.h"
#include "DirectionalLightingEffect.h"
#include "RenderManager.h"
#include "Terrain.h"


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

ObjectInstance* pGround;
ObjectInstance* pZombie;
ObjectInstance* pBob;
ObjectInstance* pPalm;

ObjectInstance* pBambooPalm;
ObjectInstance* pGroundPalm;
ObjectInstance* pSmallPlant;
ObjectInstance* pHighTree;
ObjectInstance* pRock;

glm::mat4 projectionMatrix;

glm::vec3 camPos;
float yaw;
float pitch;
MCamera camera;

SceneDecomposeEffect* pDecomposeEffect;
DepthThresholdEffect* pThresholdEffect;
GodRaysEffect* pRayEffect;
BloomEffect* pBloomEffect;
FXAAEffect* pFXAAEffect;
MultiplicativeBlendEffect* pBlendEffect;
DirectionalLightingEffect* pLightingEffect;
GLuint godRayMaskTexture;
GLuint sceneTextures[5];
GLuint finalTex;

vec3 lightPos = vec3(-1000, 0, 0);

ForestTerrain* pTerrain;

//Lua stuff
//https://eliasdaler.wordpress.com/2014/07/18/using-lua-with-cpp-luabridge/

// initializes setting
void myinit();
void GameLoop();
bool HandleEvents();

void UpdatePlayer()
{
  const float TURN_SPEED = 0.3f;
  const float MOVE_SPEED = 0.5f;

  //InputManager* im = InputManager::GetInstance();

  //Rotation
  float originalYaw = camera.GetYaw();
  float originalPitch = camera.GetPitch();
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
      translation *= 4;

    if (im->IsKeyDown(SDL_SCANCODE_LCTRL))
      translation *= 0.25f;

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

  int result = SDL_GL_SetSwapInterval(0);

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
  srand(time(NULL));

  TextureLibrary::GetInstance().InitTextureLibrary();
  ShaderLibrary::GetInstance().InitShaderLibrary();
  SoundManager::GetSoundManager()->InitSoundManager();
  FrameBuffer::Initialize();
  LuaManager::Initialize();

  LuaManager::GetInstance().CreateContext("Game.lua");

  projectionMatrix = glm::perspective(3.1416f / 2, SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 10000.f);

  TextureLibrary::GetInstance().AddTexture("", 1);
  ModelLibrary& modelLibrary = ModelLibrary::GetInstance();
  
  modelLibrary.AddModel("Bob", "Assets/Models/Bob/bob.md5mesh", false);
  modelLibrary.AddModel("Zombie", "Assets/Models/Zombie/Zombii.fbx", false);
  modelLibrary.AddModel("Ground", "Assets/Models/Ground/Ground.obj", false);
  modelLibrary.AddModel("PalmTree", "Assets/Models/PalmTree/PalmTree.obj", false);
  modelLibrary.AddModel("BambooPalm", "Assets/Models/BambooPalm/BambooPalm.obj", false);
  modelLibrary.AddModel("GroundPalm", "Assets/Models/GroundPalm/GroundPalm.obj", false);
  modelLibrary.AddModel("SmallPlant", "Assets/Models/SmallPlant/SmallPlant.obj", false);
  modelLibrary.AddModel("HighTree", "Assets/Models/HighTree/HighTree.obj", false);
  modelLibrary.AddModel("Rock", "Assets/Models/Rock/Rock.obj", false);
  modelLibrary.AddModel("Rock", "Assets/Models/Rock/Rock.obj", false);

  pTerrain = new ForestTerrain(5, 40, "Assets/HeightMaps/heightmap.png", 1);
  pTerrain->SaveTerrainToOBJ("Assets/Models/Terrain/Terrain.obj");
  modelLibrary.AddModel("ForestTerrain", "Assets/Models/Terrain/Terrain.obj", false);

  pBob = modelLibrary.GetObjectInstance("Bob");
  pGround = modelLibrary.GetObjectInstance("ForestTerrain");
  pZombie = modelLibrary.GetObjectInstance("Zombie");
  pPalm = modelLibrary.GetObjectInstance("PalmTree");

  pBambooPalm = modelLibrary.GetObjectInstance("BambooPalm");
  pGroundPalm = modelLibrary.GetObjectInstance("GroundPalm");
  pSmallPlant = modelLibrary.GetObjectInstance("SmallPlant");
  pHighTree = modelLibrary.GetObjectInstance("HighTree");
  pRock = modelLibrary.GetObjectInstance("Rock");

  pGround->SetTranslation(0, 0, 0);
  pBob->SetTranslation(-10, 0, 0);
  pZombie->SetTranslation(0, 0, 0);
  pPalm->SetTranslation(10, 0, 0);

  pBambooPalm->SetTranslation(15, 0, 5);
  pHighTree->SetTranslation(25, 0, 10);
  pRock->SetTranslation(38, 0, -5);

  pGround->SetScale(vec3(1, 1, 1));
  pBob->SetScale(vec3(0.13f, 0.13f, 0.13f));
  pZombie->SetScale(vec3(0.05f, 0.05f, 0.05f));
  pPalm->SetScale(vec3(1.5f, 1.5f, 1.5f));

  pBob->SetActiveAnimation(0);
  pZombie->SetActiveAnimation(0);

  pBob->SetPitch(-90);

  pDecomposeEffect = new SceneDecomposeEffect();
  pThresholdEffect = new DepthThresholdEffect();
  pRayEffect = new GodRaysEffect();
  pBloomEffect = new BloomEffect();
  pFXAAEffect = new FXAAEffect();
  pBlendEffect = new MultiplicativeBlendEffect();
  pLightingEffect = new DirectionalLightingEffect();

  sceneTextures[0] = CreateColourFTexture();
  sceneTextures[1] = CreateDepthTexture();
  sceneTextures[2] = CreateVec3Texture();
  sceneTextures[3] = CreateVec3Texture();
  sceneTextures[4] = CreateVec3Texture();

  godRayMaskTexture = CreateVec3Texture();
  finalTex = CreateVec3Texture();



  SoundManager::GetSoundManager()->AddSound("Music", "Assets/Sounds/ambient.wav");
  SoundManager::GetSoundManager()->PlaySound("Music", INT_MAX);

}

bool HandleEvents()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_QUIT:
        return false;
      case SDL_MOUSEMOTION:
        InputManager::GetInstance().PushEvent(MouseEvent(event.motion));
        break;
      case SDL_MOUSEBUTTONDOWN:
        InputManager::GetInstance().PushEvent(MouseEvent(event.button));
        break;
      case SDL_MOUSEBUTTONUP:
        InputManager::GetInstance().PushEvent(MouseEvent(event.button));
        break;
    }
  }
  return true;
}

bool Update()
{
  if (!HandleEvents())
    return false;

  InputManager::GetInstance().Update();

  if (InputManager::GetInstance().IsKeyDown(SDL_SCANCODE_ESCAPE))
    return false;

  UpdatePlayer();

  return true;
}

void Render()
{
  static bool renderDepth = true;

  glCullFace(GL_BACK);
  if (InputManager::GetInstance().IsKeyPressed(SDL_SCANCODE_1))
  {
    renderDepth = !renderDepth;
  }
  glEnable(GL_DEPTH_TEST);

  float time = clock() / float(CLOCKS_PER_SEC);
  vec3 tr = pZombie->GetTranslation();
  tr.z = -50 +  1.6f * time;
  pZombie->SetTranslation(tr);

  lightPos.x = -cos(PI * time / 60) * 10000;
  lightPos.y = sin(PI * time / 60) * 10000;

  pDecomposeEffect->Bind(sceneTextures[0], sceneTextures[1], sceneTextures[2], sceneTextures[3], sceneTextures[4]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
  RenderManager::GetInstance().Render(mat4(), camera.getViewMatrix(), projectionMatrix, time);
  pDecomposeEffect->Unbind();

  float camDist = length(camera.GetPosition() - lightPos);

  ////pThresholdEffect->Apply(sceneTextures[2], godRayMaskTexture, camDist);

  vec4 temp = camera.getViewMatrix() * vec4(lightPos, 1);
  vec3 vsLightPos = vec3(temp.x, temp.y, temp.z);
  float lightDist = length(vsLightPos);
  temp = projectionMatrix * vec4(vsLightPos, 1.0);
  temp.x = temp.x / temp.w;
  temp.y = temp.y / temp.w;
  vec3 ssLightPos = vec3(temp.x, temp.y, lightDist);

  if (vsLightPos.z > 0)
  {
    pLightingEffect->Apply(sceneTextures[3], godRayMaskTexture, vec3(0.5, 0.5, 0.4), normalize(-lightPos));
    pBlendEffect->Apply(sceneTextures[0], godRayMaskTexture, sceneTextures[4]);
  }
  else
  {
    pLightingEffect->Apply(sceneTextures[3], godRayMaskTexture, vec3(0.5, 0.5, 0.4), normalize(-lightPos));
    pBlendEffect->Apply(godRayMaskTexture, sceneTextures[0], sceneTextures[3]);
    pRayEffect->Apply(sceneTextures[3], sceneTextures[2], sceneTextures[4], ssLightPos);
  }
  //pBlendEffect->Apply(sceneTextures[0], godRayMaskTexture, finalTex);

  //pRayEffect->Apply(sceneTextures[0], sceneTextures[2], godRayMaskTexture, ssLightPos);
  //pBloomEffect->Apply(sceneTextures[4], finalTex, 7);
  pFXAAEffect->Apply(sceneTextures[4], finalTex, 32);
  //pFXAAEffect->Apply(godRayMaskTexture, sceneTextures[2], 8);

  if (renderDepth)
  {
    FrameBuffer::Display(finalTex);
  }
  else
  {
    FrameBuffer::Display(sceneTextures[4]);
  }

  char frameRate[32];
  sprintf_s(frameRate, "FPS: %.2f", RenderManager::GetInstance().GetFrameRate());
  //printf("%s\n", frameRate);
  DrawText(16, "Assets/Fonts/verdanab.ttf", frameRate, 0, 0, vec3(1, 1, 1));
  //glFlush();
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