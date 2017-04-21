#ifndef GLEngine_h__
#define GLEngine_h__

#include "IEngine.h"


/**
* @file GLEngine.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief This is the implemented OpenGL engine, currently the only API that is fully implemented in the engine.
*
* The basic OpenGL Engine comes with an SDL owned window for rendering to
* Comes with the standard libraries & managers ready to be used with the OpenGL & SDL API
* Shader Library
* Texture Library
* Model Library
* Sound Manager
* Input Manager
* 
* The Render and Update are broken in to two functions
* BeginRender() is called before executing lua script render stuff and then EndRender() is called afterwards
* BeginUpdate() is called before executing lua script update stuff and then EndUpdate() is called afterwards
*/

struct SDL_Window;
class LuaObjectInstanceManager;




class GLEngine : public IEngine
{

public:

  /// <summary>
  /// Creates this instance.
  /// </summary>
  /// <returns>IEngine*</returns>
  static IEngine* Create();


  /// <summary>
  /// Initialises the engine.
  /// </summary>
  /// <param name="screenWidth">Width of the screen.</param>
  /// <param name="screenHeight">Height of the screen.</param>
  virtual void Initialise(int screenWidth, int screenHeight) override;


  /// <summary>
  /// Begins the render.
  /// </summary>
  virtual void BeginRender() override;


  /// <summary>
  /// Ends the render.
  /// </summary>
  virtual void EndRender() override;


  /// <summary>
  /// Begins the update.
  /// </summary>
  /// <returns></returns>
  virtual bool BeginUpdate() override;


  /// <summary>
  /// Ends the update.
  /// </summary>
  virtual void EndUpdate() override;

private:

  /// <summary>
  /// Prevents a default instance of the <see cref="GLEngine"/> class from being created.
  /// </summary>
  GLEngine();

  /// <summary>
  /// Finalizes an instance of the <see cref="GLEngine"/> class.
  /// </summary>
  ~GLEngine();

  /// <summary>
  /// Creates the window.
  /// </summary>
  void CreateWindow();
  
  /// <summary>
  /// Initializes the SDL API.
  /// </summary>
  /// <returns></returns>
  bool InitSDL();
  
  /// <summary>
  /// Handles the input events.
  /// </summary>
  /// <returns></returns>
  bool HandleEvents();
  
  /// <summary>
  /// Initializes GLEW
  /// </summary>
  void InitGlew();
  
  /// <summary>
  /// The m screen
  /// </summary>
  SDL_Window* m_screen;

  /// <summary>
  /// The screen width
  /// </summary>
  int m_screenWidth;

  /// <summary>
  /// The screen height
  /// </summary>
  int m_screenHeight;

  /// <summary>
  /// The instance manager
  /// </summary>
  LuaObjectInstanceManager* m_instanceManager;

  virtual IShader* CreateShader(string const& name, string const& vertFilePath, string const& fragFilePath, std::vector<string> const& attributes, std::vector<string> const& uniforms) const override;

  virtual IRenderableObject* CreateRenderableObject(string const& name, string const& filename) const override;

};

#endif // GLEngine_h__
