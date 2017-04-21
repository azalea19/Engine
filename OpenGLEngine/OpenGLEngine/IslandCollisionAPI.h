
#include "LuaContext.h"
#include "LuaManager.h"


#pragma once
class IslandCollisionAPI
{
public:
	/// Expose to lua
	void IslandCollisionAPI::Expose(LuaContextHandle contextHandle, string luaAPIName);
	/// Given the current origin of a colliding AABB, returns the new origin for it that will resolve the collision with any static objects.
	LuaRef IslandCollisionAPI::Resolve(LuaRef toMoveOrigin, LuaRef toMoveBBMin, LuaRef toMoveBBMax, LuaRef staticBBMin, LuaRef staticBBMax);
	/// Check if one AABB is colliding with any in a list
	void IslandCollisionAPI::Check1ToMany(LuaRef min, LuaRef max, LuaRef manyList, int listSize, LuaContextHandle handle);

};

