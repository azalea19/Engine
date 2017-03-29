/*

#include "IEngine.h"



Engine* Engine::Create()
{
  return new Engine();
}

void Engine::~Engine()
{

}

void Engine::Initialise(int width, int height)
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
  //MVCView::screen = 

  int result = SDL_GL_SetSwapInterval(0);

  SDL_SetRelativeMouseMode(SDL_TRUE);
  return true;







  m_screen = SDL_CreateWindow("Arch Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

  SDL_GL_CreateContext(MVCView::screen);







  InitGlew();

  TextureLibrary::GetInstance().InitTextureLibrary();
  ShaderLibrary::GetInstance().InitShaderLibrary();
  SoundManager::GetInstance().InitSoundManager();
  FrameBuffer::Initialize();
  LuaManager::Initialize();

  m_instanceManager = LuaInstanceManager.GetInstance();
}

void Engine::SetDimensions(int width, int height)
{
  //SDL_SetWindowSize
}

void Engine::AddObjectInstance(string modelName)
{
  return m_instanceManager->GetInstance();
}

void Engine::BeginRender()
{

}

void Engine::EndRender()
{

}

void Engine::Engine()
{

}

*/