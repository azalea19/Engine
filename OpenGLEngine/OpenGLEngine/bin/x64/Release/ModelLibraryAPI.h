#pragma once

#include "LuaContext.h"
#include "LuaManager.h"
#include "ModelLibrary.h"

/**
* @file ModelLibraryAPI.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief An API that allows the user to expose the required functions to the Lua.
*
*/

class ModelLibraryAPI
{
public:

  /// <summary>
  /// Adds the model.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <param name="path">The path.</param>
  /// <param name="normalized">if set to <c>true</c> [normalized].</param>
  static void AddModel(string const& name, string const& path, bool normalized);

  /// <summary>
  /// Exposes the API functions.
  /// </summary>
  /// <param name="contextHandle">The context handle.</param>
  /// <param name="luaAPIName">Name of the lua API.</param>
  static void Expose(LuaContextHandle contextHandle, string luaAPIName);
};

