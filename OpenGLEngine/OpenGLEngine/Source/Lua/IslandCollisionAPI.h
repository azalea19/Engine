/**
* @file   IslandCollisionAPI.h
* @Author Elizabeth Haynes
* @date   S1, 2017
* @brief  Lua API for checking collisions and resolving them with the island method
*/
#include "LuaContext.h"
#include "LuaManager.h"

#include "MathAPI.h"
#include "IslandCollision.h"


#pragma once
class IslandCollisionAPI
{
public:
	/// <summary>
	/// Expose API to lua
	/// </summary>
	/// <param name="contextHandle">Lua context handle</param>
	/// <param name="contextHandle">API name</param>
	/// <returns>bool</returns>
	static void IslandCollisionAPI::Expose(LuaContextHandle contextHandle, string luaAPIName);

	/// <summary>
	/// Given the current origin of a colliding AABB, returns the new origin for it
	/// that will resolve the collision with any static objects.
	/// Exposes Resolve function through Lua API.
	/// </summary>
	/// <param name="toMoveOrigin">Origin of current bounding box to move when colliding</param>
	/// <param name="toMoveBBi">Current bounding box to move when colliding</param>
	/// <param name="manyList">Table of many Vec3, in pairs of min and then max of AABBs.</param>
	/// <param name="listSize">Number of AABBs in the manyList table (half the number of values)</param>
	/// <param name="incSize">Size of movement increments</param>
	/// <param name="handle">Lua context handle</param>
	/// <returns>LuaRef</returns>
	static LuaRef IslandCollisionAPI::Resolve(LuaRef toMoveOrigin, LuaRef toMoveBBi, LuaRef manyList, int listSize, float incSize, LuaContextHandle handle);

	/// <summary>
	/// Check if one AABB is colliding with any in a list. todo Probably should be in AABB class instead.
	/// Exposes Check function through Lua API.
	/// </summary>
	/// <param name="min">Table vec3 min point of AABB</param>
	/// <param name="max">Table vec3 max point of AABB</param>
	/// <param name="manyList">Table of many Vec3, in pairs of min and then max of AABBs.</param>
	/// <param name="listSize">Number of AABBs in the manyList table (half the number of values)</param>
	/// <param name="handle">Lua context handle</param>
	static bool IslandCollisionAPI::CheckAnyCollision(LuaRef thisbox, LuaRef manyList, int listSize);

};

