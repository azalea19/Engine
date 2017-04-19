#ifndef IEngine_h__
#define IEngine_h__

#include "types.h"

/**
* @file IEngine.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief This is the engine interface that allows for API independence.
* The engine interface is designed to be used when creating an engine that uses a different API.
* Users may inherit from the IEngine interface to get access to the engine functionality in the lua,
* while being able to implement the implantation using a different API.
*/

enum GraphicsAPI
{
  API_OPEN_GL,
  API_DIRECT_X,
  API_VULKAN
};

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
  /// Sets the screen dimensions.
  /// </summary>
  virtual void SetScreenDimensions() = 0;

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

};
#endif // IEngine_h__
