#ifndef EngineAPI_h__
#define EngineAPI_h__

#include "LuaContext.h"
#include "LuaManager.h"
#include "IEngine.h"
#include <memory>

/**
* @file EngineAPI.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief An API that allows the user to expose the required engine functions to the Lua.
*
*/

enum GraphicsAPI : int
{
  API_OPEN_GL = 0,
  API_DIRECT_X = 1,
  API_VULKAN = 2
};

class EngineAPI
{

public:

  /// <summary>
  /// Exposes the functions in the API.
  /// </summary>
  /// <param name="contextHandle">The context handle.</param>
  /// <param name="luaAPIName">Name of the lua API.</param>

  /// <summary>
  /// Creates the engine of specified API.
  /// </summary>
  /// <param name="api">The API.</param>
  static void Create(int api);

  /// <summary>
  /// Exposes the specified functions.
  /// </summary>
  /// <param name="contextHandle">The context handle.</param>
  /// <param name="luaAPIName">Name of the lua API.</param>
  static void Expose(LuaContextHandle contextHandle, string luaAPIName);

  /// <summary>
  /// Gets the engine.
  /// </summary>
  /// <returns></returns>
  static IEngine* GetEngine();

private:

  static std::unique_ptr<IEngine> s_engine;

};


#endif // EngineAPI_h__
