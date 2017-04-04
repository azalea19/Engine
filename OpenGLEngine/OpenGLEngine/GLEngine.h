#ifndef GLEngine_h__
#define GLEngine_h__

#include "IEngine.h"

struct SDL_Window;
class LuaInstanceManager;

//Basic OpenGL Engine comes with an SDL owned window for rendering to
//Comes with the standard libraries & managers ready to be used with the OpenGL & SDL API
//Shader Library
//Texture Library
//Model Library
//Sound Manager
//Input Manager
//It also comes with a Lua Manager that interfaces with the library and manager lua interfaces

//The Render and Update are broken in to two functions 
//BeginRender() is called before executing lua script render stuff and then EndRender() is called after


class GLEngine : public IEngine
{

public:

  static IEngine* Create();


  virtual void Initialise(int screenWidth, int screenHeight) override;


  virtual void SetScreenDimensions() override;


  virtual void BeginRender() override;


  virtual void EndRender() override;


  virtual bool BeginUpdate() override;


  virtual void EndUpdate() override;

private:

  GLEngine();
  ~GLEngine();

  void CreateWindow();
  bool InitSDL();
  bool HandleEvents();
  void InitGlew();
  
  SDL_Window* m_screen;
  int m_screenWidth;
  int m_screenHeight;
  LuaInstanceManager* m_instanceManager; 

};

#endif // GLEngine_h__
