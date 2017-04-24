#pragma once

#include "LuaBridge.h"

#include "LuaContext.h"
#include "LuaManager.h"
#include "Types.h"
#include "LuaObjectInstanceManager.h"
#include "MathAPI.h"

/**
* @file   AABBAPI.h
* @Author Elizabeth Haynes
* @date   S1, 2017
* @brief  Lua API for getting Axis Aligned Bounding Boxes
*/


class AABBAPI
{
public:

	/// <summary>
	/// Gets the aabb from an object instance handle.
	/// </summary>
	/// <param name="handle">The object instance handle.</param>
	/// <param name="cHandle">The context handle.</param>
	/// <returns></returns>
	static LuaRef GetAABB(int handle, LuaContextHandle cHandle);
	/// <summary>
	/// Moves the specified bbox.
	/// </summary>
	/// <param name="bbox">The bbox.</param>
	/// <param name="oldPos">The old position.</param>
	/// <param name="newPos">The new position.</param>
	/// <param name="cHandle">The context handle.</param>
	/// <returns></returns>
	static LuaRef Move(LuaRef bbox, LuaRef oldPos, LuaRef newPos, LuaContextHandle cHandle);

	/// <summary>
	/// Exposes the specified context handle.
	/// </summary>
	/// <param name="contextHandle">The context handle.</param>
	/// <param name="luaAPIName">Name of the lua API.</param>
	static void Expose(LuaContextHandle contextHandle, string luaAPIName);

private:

	//static std::vector<vec3> GetMin(int instHandle);
	//static void GetMax(int instHandle);

};

