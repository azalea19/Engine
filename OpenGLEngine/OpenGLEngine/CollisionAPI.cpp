#include "CollisionAPI.h"

bool CollisionAPI::RayToAABB(LuaRef ray, LuaRef aabb)
{
	mRay myRay = FromLuaTable<mRay>(ray);
	mAABB myAABB = FromLuaTable<mAABB>(aabb);
	bool a = Intersects(myAABB, myRay);

	return a;
}

void CollisionAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "rayToAABB", RayToAABB);
}