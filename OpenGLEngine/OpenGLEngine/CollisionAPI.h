#pragma once


#include "LuaContext.h"
#include "LuaManager.h"
#include "MathAPI.h"
#include "GeometricPrimitives.h"
#include "PrimitiveCollisions.h"

/// <summary>
/// API for checking primitive collisions in Lua
/// Author Elizabeth Haynes
/// </summary>
class CollisionAPI
{
public:	
	/// <summary>
	/// Checks collision of ray and AABB
	/// </summary>
	/// <param name="ray">The ray.</param>
	/// <param name="aabb">The AABB.</param>
	/// <returns></returns>
	static bool RayToAABB(LuaRef ray, LuaRef aabb);
	/// <summary>
	/// Exposes this lua API.
	/// </summary>
	/// <param name="contextHandle">The context handle.</param>
	/// <param name="luaAPIName">Name of the lua API.</param>
	static void Expose(LuaContextHandle contextHandle, string luaAPIName);

};

