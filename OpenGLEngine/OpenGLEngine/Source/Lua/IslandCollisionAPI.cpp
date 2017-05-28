#include "IslandCollisionAPI.h"
#include "CollisionAPI.h"

bool IslandCollisionAPI::CheckAnyCollision(LuaRef thisbox)
{
<<<<<<< HEAD

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
	
	return IslandCollision::Check(toMoveBB, manyBB, listSize);

	//todo write
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

	return IslandCollision::CheckAndGetIndex(toMoveBB, manyBB, listSize);

	//todo write
=======
  mAABB toMoveBB;
  toMoveBB.max = FromLuaTable<vec3>(thisbox["max"]);
  toMoveBB.min = FromLuaTable<vec3>(thisbox["min"]);
  return IslandCollision::Check(toMoveBB);
>>>>>>> 36947cce270eff9264ef4a438bd106f1a7a57b9e
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
	pContext->ExposeFunction(luaAPIName, "resolve", Resolve);
	
	//pContext->ExposeFunction(luaAPIName, "testRender", TestRender);
	//pContext->ExposeFunction(luaAPIName, "updatePlayer", UpdatePlayer);
}