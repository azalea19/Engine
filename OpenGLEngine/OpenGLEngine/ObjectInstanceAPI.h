#pragma once
#include "LuaContext.h"
#include "LuaInstanceManager.h"
#include "LuaManager.h"
#include "ShaderLibrary.h"
#include "MPlayer.h"
#include "MCamera.h"

typedef int InstanceHandle;


/**
* @file ObjectInstanceAPI.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief An API that allows the user to expose the required functions to the Lua.
*
*/

class ObjectInstanceAPI
{
public:

  /// <summary>
  /// Gets the instance.
  /// </summary>
  /// <param name="instHandle">The instance handle.</param>
  /// <returns></returns>
  static ObjectInstance * GetInstance(InstanceHandle instHandle);
	
  /// <summary>
  /// Sets the translation.
  /// </summary>
  /// <param name="instHandle">The instance handle.</param>
  /// <param name="x">The x.</param>
  /// <param name="y">The y.</param>
  /// <param name="z">The z.</param>
  static void SetTranslation(InstanceHandle instHandle, float x, float y, float z);
	
  /// <summary>
  /// Exposes the API functions.
  /// </summary>
  /// <param name="contextHandle">The context handle.</param>
  /// <param name="luaAPIName">Name of the lua API.</param>
  static void Expose(LuaContextHandle contextHandle, string luaAPIName);

};

