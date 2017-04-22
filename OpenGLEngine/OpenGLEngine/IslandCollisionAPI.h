/**
* @file   IslandCollisionAPI.h
* @Author Elizabeth Haynes
* @date   S1, 2017
* @brief  Lua API for checking collisions and resolving them with the island method
*/
#include "LuaContext.h"
#include "LuaManager.h"


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
	/// <param name="toMoveBB">Current bounding box to move when colliding</param>
	/// <param name="staticBB">Static bounding box</param>
	/// <param name="inc">Size of movement increments</param>
	/// <returns>LuaRef</returns>
	static LuaRef IslandCollisionAPI::Resolve(LuaRef toMoveOrigin, LuaRef toMoveBBMin, LuaRef toMoveBBMax, LuaRef staticBBMin, LuaRef staticBBMax);
	
	/// <summary>
	/// Check if one AABB is colliding with any in a list.
	/// Exposes Check function through Lua API.
	/// </summary>
	/// <param name="min">Table vec3 min point of AABB</param>
	/// <param name="max">Table vec3 max point of AABB</param>
	/// <param name="manyList">Table of many Vec3, in pairs of min and then max of AABBs.</param>
	/// <param name="listSize">Number of AABBs in the manyList table (half the number of values)</param>
	/// <param name="handle">Lua context handle</param>
	static void IslandCollisionAPI::CheckAnyCollision(LuaRef min, LuaRef max, LuaRef manyList, int listSize, LuaContextHandle handle);

};

