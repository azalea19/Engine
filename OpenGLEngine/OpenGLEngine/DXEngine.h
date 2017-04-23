#ifndef DXEngine_h__
#define DXEngine_h__

#include "IEngine.h"

/**
* @file DXEngine.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief An example of how a engine of a different API (DirectX) would be implemented. 
*
*
*/

class DXEngine : public IEngine
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



  /// <summary>
  /// Creates the shader.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <param name="vertFilePath">The vert file path.</param>
  /// <param name="fragFilePath">The frag file path.</param>
  /// <param name="attributes">The attributes.</param>
  /// <param name="uniforms">The uniforms.</param>
  /// <returns></returns>
  virtual IShader* CreateShader(string const& name, string const& vertFilePath, string const& fragFilePath, std::vector<string> const& attributes, std::vector<string> const& uniforms) const override;


  /// <summary>
  /// Creates the renderable object.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <param name="filename">The filename.</param>
  /// <returns></returns>
  virtual IRenderableObject* CreateRenderableObject(string const& name, string const& filename) const override;


  /// <summary>
  /// Creates the input handler.
  /// </summary>
  /// <returns></returns>
  virtual IInputHandler* CreateInputHandler() override;

private:

  /// <summary>
  /// Prevents a default instance of the <see cref="DXEngine"/> class from being created.
  /// </summary>
  DXEngine();

  /// <summary>
  /// Finalizes an instance of the <see cref="DXEngine"/> class.
  /// </summary>
  virtual ~DXEngine() override;

};

#endif // DXEngine_h__
