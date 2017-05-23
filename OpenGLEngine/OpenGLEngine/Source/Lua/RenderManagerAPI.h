#ifndef RenderManagerAPI_h__
#define RenderManagerAPI_h__


#include "LuaContext.h"
#include "LuaManager.h"
#include "MathAPI.h"
#include "Types.h"


/**
* @file RenderManagerAPI.h
* @Author Elizabeth Haynes
* @date   S1, 2017
* @brief API for rendering with the engine through a Lua interface
*/

class RenderManagerAPI
{
public:

  /// <summary>
  /// Renders the object.
  /// </summary>
  /// <param name="camID">The cam identifier.</param>
  /// <param name="time">The time.</param>
  /// <param name="instanceHandle">The instance handle.</param>
  /// <param name="lightingApplied">The lighting applied.</param>
  static void RenderManagerAPI::RenderObject(int camID, float time, int instanceHandle, int lightingApplied);

  /// <summary>
  /// Begins the render.
  /// </summary>
  static void RenderManagerAPI::BeginRender();
  /// <summary>
  /// Ends the render.
  /// </summary>
  static void RenderManagerAPI::EndRender();
  /// <summary>
  /// Sets the fill mode (wireframe = 0, fill = 1).
  /// </summary>
  /// <param name="fillMode">The fill mode.</param>
  static void RenderManagerAPI::SetFillMode(int fillMode);

  /// <summary>
  /// Applies post processing and displays resulting texture on screen
  /// </summary>
  static void Present(int camID);

  /// <summary>
  /// Exposes the lua API
  /// </summary>
  /// <param name="contextHandle">The context handle.</param>
  /// <param name="luaAPIName">Name of the lua API.</param>
  static void Expose(LuaContextHandle contextHandle, string luaAPIName);

};
#endif // RenderManagerAPI_h__