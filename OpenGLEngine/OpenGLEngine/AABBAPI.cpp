#include "AABBAPI.h"



LuaRef AABBAPI::GetAABB(int handle, LuaContextHandle cHandle)
{
	LuaRef AABBtable = luabridge::newTable(LuaManager::GetInstance().GetContext(cHandle)->GetLuaState());
	std::vector<vec3> bbox = LuaObjectInstanceManager::GetInstance(cHandle)->GetRenderableObject()->GetAABB();

	AABBtable["min"] = ToLuaTable(bbox[0],cHandle);
	AABBtable["max"] = ToLuaTable(bbox[1],cHandle);

	return AABBtable;
}

LuaRef AABBAPI::Move(LuaRef bbox, LuaRef oldPos, LuaRef newPos, LuaContextHandle cHandle)
{
	vec3 bboxmin = FromLuaTable<vec3> (bbox["min"]);
	vec3 bboxmax = FromLuaTable<vec3>(bbox["max"]);
	vec3 oldposvec = FromLuaTable<vec3>(oldPos);
	vec3 newposvec = FromLuaTable<vec3>(newPos);

	vec3 diff = (newposvec - oldposvec);
	vec3 newMin = bboxmin + diff;
	vec3 newMax = bboxmax + diff;


	LuaRef newAABB = luabridge::newTable(LuaManager::GetInstance().GetContext(cHandle)->GetLuaState());

	newAABB["min"] = ToLuaTable(newMin,cHandle);
	newAABB["max"] = ToLuaTable(newMax,cHandle);

	return newAABB;
}


void AABBAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{

		LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
		pContext->ExposeFunction(luaAPIName, "getAABB", GetAABB);
		pContext->ExposeFunction(luaAPIName, "move", Move);

}