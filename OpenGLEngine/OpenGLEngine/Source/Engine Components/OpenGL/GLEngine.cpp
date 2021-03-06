#include "GLEngine.h"
#include "InputManager.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "GL/glew.h"
#include "LuaManager.h"
#include "SDL_ttf.h"
#include "Shader.h"
#include "RenderableObject.h"
#include "Screen.h"
#include "GLInputHandler.h"
#include "GLRenderManager.h"
#include "GLSoundManager.h"

IEngine* GLEngine::Create()
{
  return new GLEngine();
}

void GLEngine::InitGlew()
{
  //Initialize GLEW
  glewExperimental = GL_TRUE;
  GLenum glewError = glewInit();

  if (glewError != GLEW_OK)
  {
    printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
    getchar();
  }
}

IShader* GLEngine::CreateShader(string const& name, string const& vertFilePath, string const& fragFilePath, std::vector<string> const& attributes, std::vector<string> const& uniforms) const
{
  return new Shader(name, vertFilePath, fragFilePath, attributes, uniforms);
}

IRenderableObject* GLEngine::CreateRenderableObject(string const& name, string const& filename) const
{
  return new RenderableObject(name, filename);
}

IInputHandler* GLEngine::CreateInputHandler()
{
  return new GLInputHandler();
}

IRenderManager* GLEngine::CreateRenderManager()
{
  return new GLRenderManager();
}

GLEngine::GLEngine()
{
}

void GLEngine::CreateWindow()
{
  m_screen = SDL_CreateWindow("Arch Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_screenWidth, m_screenHeight, SDL_WINDOW_OPENGL);
  SDL_GL_CreateContext(m_screen);
}

bool GLEngine::InitSDL()
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

  int result = SDL_GL_SetSwapInterval(0);

  SDL_SetRelativeMouseMode(SDL_TRUE);
  return true;
}


void GLEngine::Initialise(int screenWidth, int screenHeight)
{
  m_screenWidth = screenWidth;
  m_screenHeight = screenHeight;

  vec2i xy = vec2i(screenWidth, screenHeight);
  SetScreenDimensions(xy);
  
  //Init SDL & create a window
  InitSDL();

  CreateWindow();

  //Init glew
  InitGlew();


  //Seed random generator
  srand(uint(time(NULL)));

  //Init Lua manager so we can start ordering the engine to do stuff
  LuaManager::Initialize();

  //Clear screen for rendering
  glClearColor(0, 0, 0, 1.f);


}


void GLEngine::BeginRender()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
}

void GLEngine::EndRender()
{
  glFlush();
  SDL_GL_SwapWindow(m_screen);
}

bool GLEngine::BeginUpdate()
{
  InputManager::GetInstance().Update();

  return true;
}

void GLEngine::EndUpdate()
{
}

ISoundManager* GLEngine::CreateSoundManager()
{
  return new GLSoundManager();
}

GLEngine::~GLEngine()
{

}

