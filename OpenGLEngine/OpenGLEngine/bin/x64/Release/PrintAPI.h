#ifndef PrintAPI_h__
#define PrintAPI_h__

#include "LuaContext.h"
#include "LuaManager.h"


/**
* @file PrintAPI.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief An API that allows the user to expose the required functions to the Lua.
*
*/

class PrintAPI
{
public:

  /// <summary>
  /// Exposes the API functions.
  /// </summary>
  /// <param name="contextHandle">The context handle.</param>
  /// <param name="luaAPIName">Name of the lua API.</param>
  static void Expose(LuaContextHandle contextHandle, string luaAPIName);

};
#endif // PrintAPI_h__