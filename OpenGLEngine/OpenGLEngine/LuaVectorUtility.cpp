#include "LuaVectorUtility.h"

LuaRef LuaVectorUtility::Normalize(float x, float y, float z)
{
	vec3 vec(x, y, z);
	vec = normalize(vec);
	return ToLuaTable(vec, LuaManager::GetInstance().GetContext(0)->GetLuaState());
}

 /*
LuaRef LuaVectorUtility::Add(float x1, float y1, float z1, float x2, float y2, float z2)
{
	//float val[3];
	vec3 vec1(x1, y1, z1);
	vec3 vec2(x2, y2, z2);
	vec3 finalVec = vec1 + vec2;
	return ToLuaTable(finalVec, LuaManager::GetInstance().GetContext(0)->GetLuaState());//finalVec, state);
}
*/

LuaRef LuaVectorUtility::AddVector(LuaRef a, LuaRef b)
{
	//float val[3];
	vec3 vec1 = FromLuaTable<vec3>(a);
	vec3 vec2 = FromLuaTable<vec3>(b);
	vec3 finalVec = vec1 + vec2;
	return ToLuaTable(finalVec, LuaManager::GetInstance().GetContext(0)->GetLuaState());//finalVec, state);
}


/// Removes vec3 b from a
LuaRef LuaVectorUtility::SubtractVector(LuaRef a, LuaRef b)
{
	//float val[3];
	vec3 vec1 = FromLuaTable<vec3>(a);
	vec3 vec2 = FromLuaTable<vec3>(b);
	vec3 finalVec = vec1 - vec2;
	return ToLuaTable(finalVec, LuaManager::GetInstance().GetContext(0)->GetLuaState());//finalVec, state);
}


LuaRef LuaVectorUtility::MultiplyFloat(float x, float y, float z, float flt)
{
	vec3 vec(x, y, z);
	vec3 finalVec = vec * flt;
	return ToLuaTable(finalVec, LuaManager::GetInstance().GetContext(0)->GetLuaState());//finalVec, state);

}


void LuaVectorUtility::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "normalize", Normalize);
	pContext->ExposeFunction(luaAPIName, "addVector", AddVector);
	pContext->ExposeFunction(luaAPIName, "subtractVector", SubtractVector);

	pContext->ExposeFunction(luaAPIName, "multiplyFloat", MultiplyFloat);


}