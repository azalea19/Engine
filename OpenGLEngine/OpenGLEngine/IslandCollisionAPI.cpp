#include "IslandCollisionAPI.h"


void IslandCollisionAPI::Check1ToMany(LuaRef min, LuaRef max, LuaRef manyList, int listSize, LuaContextHandle handle)
{

}

LuaRef IslandCollisionAPI::Resolve(LuaRef toMoveOrigin, LuaRef toMoveBBMin, LuaRef toMoveBBMax, LuaRef staticBBMin, LuaRef staticBBMax)
{

}



void IslandCollisionAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "render", Render);
	pContext->ExposeFunction(luaAPIName, "renderFromCamera", RenderFromCamera);
	pContext->ExposeFunction(luaAPIName, "addObject", AddObject);
	pContext->ExposeFunction(luaAPIName, "initialise", Initialise);

	//pContext->ExposeFunction(luaAPIName, "testRender", TestRender);
	//pContext->ExposeFunction(luaAPIName, "updatePlayer", UpdatePlayer);
}