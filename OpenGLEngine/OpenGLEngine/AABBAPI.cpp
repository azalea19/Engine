#include "AABBAPI.h"



LuaRef AABBAPI::GetAABB(int handle, LuaContextHandle cHandle)
{
	LuaRef AABBtable = luabridge::newTable(LuaManager::GetInstance().GetContext(cHandle)->GetLuaState());
	std::vector<vec3> bbox = LuaObjectInstanceManager::GetInstance(cHandle)->GetRenderableObject()->GetAABB();

	AABBtable["min"] = bbox[0];
	AABBtable["max"] = bbox[1];

	return AABBtable;
}

LuaRef AABBAPI::Move(LuaRef bbox, LuaRef oldPos, LuaRef newPos, LuaContextHandle cHandle)
{
	LuaRef min = bbox["min"];
	vec3 bboxmin = FromLuaTable<vec3> (min);
	vec3 bboxmax = FromLuaTable<vec3>(bbox["max"]);
	vec3 oldposvec = FromLuaTable<vec3>(oldPos);
	vec3 newposvec = FromLuaTable<vec3>(newPos);

	vec3 diff = (newposvec - oldposvec);
	vec3 newMin = bboxmin + diff;
	vec3 newMax = bboxmax + diff;


	LuaRef newAABB = luabridge::newTable(LuaManager::GetInstance().GetContext(cHandle)->GetLuaState());

	newAABB["min"] = newMin;
	newAABB["max"] = newMax;

	return newAABB;
}


void AABBAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{

		LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
		pContext->ExposeFunction(luaAPIName, "getAABB", GetAABB);
		pContext->ExposeFunction(luaAPIName, "move", Move);

}