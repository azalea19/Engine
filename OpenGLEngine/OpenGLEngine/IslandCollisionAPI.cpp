#include "IslandCollisionAPI.h"


void IslandCollisionAPI::CheckAnyCollision(LuaRef min, LuaRef max, LuaRef manyList, int listSize, LuaContextHandle handle)
{
	//todo write
}

LuaRef IslandCollisionAPI::Resolve(LuaRef toMoveOrigin, LuaRef toMoveBBMin, LuaRef toMoveBBMax, LuaRef staticBBMin, LuaRef staticBBMax)
{
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