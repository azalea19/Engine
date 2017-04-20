#ifndef EngineAPI_h__
#define EngineAPI_h__

#include "LuaContext.h"
#include "LuaManager.h"
#include "IEngine.h"

/**
* @file EngineAPI.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief An API that allows the user to expose the required engine functions to the Lua.
*
*/

class EngineAPI
{

public:

  static IEngine* s_engine;

  /// <summary>
  /// Exposes the functions in the API.
  /// </summary>
  /// <param name="contextHandle">The context handle.</param>
  /// <param name="luaAPIName">Name of the lua API.</param>
  static void Expose(LuaContextHandle contextHandle, string luaAPIName);
 
};


#endif // EngineAPI_h__
