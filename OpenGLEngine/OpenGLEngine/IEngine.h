#ifndef IEngine_h__
#define IEngine_h__

#include "types.h"
#include "IShader.h"
#include "IRenderableObject.h"
#include "IInputHandler.h"

/**
* @file IEngine.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief This is the engine interface that allows for API independence.
* The engine interface is designed to be used when creating an engine that uses a different API.
* Users may inherit from the IEngine interface to get access to the engine functionality in the lua,
* while being able to implement the implantation using a different API.
*/



enum WindowAPI
{
  API_SDL,
  API_GLFW,
  API_FREEGLUT
};

class IEngine 
{
public:

  /// <summary>
  /// Initialises the engine.
  /// </summary>
  /// <param name="screenWidth">Width of the screen.</param>
  /// <param name="screenHeight">Height of the screen.</param>
  virtual void Initialise(int screenWidth, int screenHeight) = 0;

  /// <summary>
  /// Finalizes an instance of the <see cref="IEngine" /> class.
  /// </summary>
  virtual ~IEngine() = 0 {}

  /// <summary>
  /// Begins the render.
  /// </summary>
  virtual void BeginRender() = 0;

  /// <summary>
  /// Ends the render.
  /// </summary>
  virtual void EndRender() = 0;

  /// <summary>
  /// Begins the update.
  /// </summary>
  /// <returns>bool</returns>
  virtual bool BeginUpdate() = 0;

  /// <summary>
  /// Ends the update.
  /// </summary>
  virtual void EndUpdate() = 0;


  /// <summary>
  /// Creates the shader.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <param name="vertFilePath">The vert file path.</param>
  /// <param name="fragFilePath">The frag file path.</param>
  /// <param name="attributes">The attributes.</param>
  /// <param name="uniforms">The uniforms.</param>
  /// <returns></returns>
  virtual IShader* CreateShader(string const& name, string const& vertFilePath, string const& fragFilePath, std::vector<string> const& attributes, std::vector<string> const& uniforms) const = 0;

  /// <summary>
  /// Creates the renderable object.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <param name="filename">The filename.</param>
  /// <returns></returns>
  virtual IRenderableObject* CreateRenderableObject(string const& name, string const& filename) const = 0;

  /// <summary>
  /// Creates the input handler.
  /// </summary>
  /// <returns></returns>
  virtual IInputHandler* CreateInputHandler() = 0;


};
#endif // IEngine_h__
