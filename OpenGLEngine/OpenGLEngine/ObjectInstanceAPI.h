#pragma once
#include "LuaContext.h"
#include "LuaObjectInstanceManager.h"
#include "LuaManager.h"
#include "ShaderLibrary.h"
#include "MPlayer.h"
#include "MCamera.h"
#include "ObjectInstance.h"

typedef int InstanceHandle;


/**
* @file ObjectInstanceAPI.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief An API that exposes the required Object Instance functions to the Lua.
* Comments - maddy & liz
* API funcs SetAnimation - nathan
*/

class ObjectInstanceAPI
{
public:
	/// <summary>
	/// Sets affine transformable orientation of object instance.
	/// </summary>
	/// <param name="instHandle">The instance handle.</param>
	/// <param name="in1">x value.</param>
	/// <param name="in2">The instance handle.</param>
	/// <param name="in3">The instance handle.</param>


	static void SetOrientation(InstanceHandle instHandle, float in1, float in2, float in3);
	/// <summary>
	/// Sets the scale.
	/// </summary>
	/// <param name="in1">Scale x value.</param>
	/// <param name="in2">Scale y value.</param>
	/// <param name="in3">Scale z value.</param>
	static void SetScale(InstanceHandle instHandle, float in1, float in2, float in3);

	/// <summary>
	/// Sets the active animation.
	/// </summary>
	/// <param name="animationIndex">Index of the animation.</param>
	static void SetAnimation(InstanceHandle instHandle, bool isAnimated);

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

