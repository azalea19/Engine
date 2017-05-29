#include "IslandCollisionAPI.h"
#include "CollisionAPI.h"

bool IslandCollisionAPI::CheckAnyCollision(LuaRef thisbox)
{

  mAABB toMoveBB;
  toMoveBB.max = FromLuaTable<vec3>(thisbox["max"]);
  toMoveBB.min = FromLuaTable<vec3>(thisbox["min"]);
  return IslandCollision::Check(toMoveBB);
	return false;
}


bool Check(mAABB a, std::vector<mAABB> list, int listSize)
{

	for (int i = 0; i < listSize; i++)
	{
		if (Intersects(a, list[i]))
		{
			return true;
		}
	}
	return false;
}

int IslandCollisionAPI::CheckAnyCollisionGetIndex(LuaRef thisbox, LuaRef manyList, int listSize)
{
	mAABB toMoveBB;
	toMoveBB.max = FromLuaTable<vec3>(thisbox["max"]);
	toMoveBB.min = FromLuaTable<vec3>(thisbox["min"]);
	std::vector<mAABB> manyBB;
	mAABB bbox;
	for (int i = 0; i < listSize; i++)
	{
		bbox.max = FromLuaTable<vec3>(LuaRef(manyList[i + 1])["max"]);
		bbox.min = FromLuaTable<vec3>(LuaRef(manyList[i + 1])["min"]);
		manyBB.push_back(bbox);
	}

	return Check(toMoveBB, manyBB, listSize);
}

LuaRef IslandCollisionAPI::Resolve(LuaRef toMoveOrigin, LuaRef toMoveBBi, LuaContextHandle handle)
{

	mAABB toMoveBB;
	toMoveBB.max = FromLuaTable<vec3>(toMoveBBi["max"]);
	toMoveBB.min = FromLuaTable<vec3>(toMoveBBi["min"]);

	std::vector<mAABB> manyBB;

	vec3 newOrigin = IslandCollision::Resolve(FromLuaTable<vec3>(toMoveOrigin), toMoveBB);

	return ToLuaTable(newOrigin, handle);
}



void IslandCollisionAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "checkAnyCollision", CheckAnyCollision);
	pContext->ExposeFunction(luaAPIName, "checkAnyCollisionGetIndex", CheckAnyCollisionGetIndex);
	pContext->ExposeFunction(luaAPIName, "check", Check);
	pContext->ExposeFunction(luaAPIName, "resolve", Resolve);
}


//std::cout << "Checking collision with... MIN: " << a.min.x << "," << a.min.z << "," << a.min.z << ", MAX: " << a.max.x << "," << a.max.y << "," << a.max.z << "//  ";
