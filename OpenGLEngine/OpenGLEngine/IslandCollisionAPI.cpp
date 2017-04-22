#include "IslandCollisionAPI.h"


bool IslandCollisionAPI::CheckAnyCollision(LuaRef thisbox, LuaRef manyList, int listSize)
{

	mAABB toMoveBB;
	toMoveBB.max = FromLuaTable<vec3>(thisbox["max"]);
	toMoveBB.min = FromLuaTable<vec3>(thisbox["min"]);

	mAABB * manyBB;
	for (int i = 0; i < listSize; i++)
	{
		manyBB[i].max = FromLuaTable<vec3>(manyList[i+1]["max"]);
		manyBB[i].min = FromLuaTable<vec3>(manyList[i+1]["min"]);
	}
	
	
	return IslandCollision::Check(toMoveBB, manyBB, listSize);

	//todo write



}

LuaRef IslandCollisionAPI::Resolve(LuaRef toMoveOrigin, LuaRef toMoveBBMin, LuaRef toMoveBBMax, LuaRef staticBBMin, LuaRef staticBBMax, LuaContextHandle handle)
{

	mAABB toMoveBB;
	toMoveBB.max = FromLuaTable<vec3>(toMoveBBMax);
	toMoveBB.min = FromLuaTable<vec3>(toMoveBBMax);

	mAABB staticBB;
	staticBB.max = FromLuaTable<vec3>(toMoveBBMax);
	staticBB.min = FromLuaTable<vec3>(toMoveBBMax);

	vec3 newOrigin = IslandCollision::Resolve(FromLuaTable<vec3>(toMoveOrigin), toMoveBB, staticBB, 1);


	return ToLuaTable(newOrigin, handle);
	//todo write
}



void IslandCollisionAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "checkAnyCollision", CheckAnyCollision);
	pContext->ExposeFunction(luaAPIName, "resolve", Resolve);

	//pContext->ExposeFunction(luaAPIName, "testRender", TestRender);
	//pContext->ExposeFunction(luaAPIName, "updatePlayer", UpdatePlayer);
}