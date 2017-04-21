#include "LuaVectorUtility.h"



//vec3 * 1/magnitude
LuaRef LuaVectorUtility::vec3_Normalize(LuaRef value, LuaContextHandle contextHandle)
{
  vec3 vec = FromLuaTable<vec3>(value);
	vec = normalize(vec);
	return ToLuaTable(vec, contextHandle);
}

//vec3 + vec3
LuaRef LuaVectorUtility::vec3_Sum(LuaRef a, LuaRef b, LuaContextHandle contextHandle)
{
	vec3 vec1 = FromLuaTable<vec3>(a);
	vec3 vec2 = FromLuaTable<vec3>(b);
	vec3 finalVec = vec1 + vec2;
	return ToLuaTable(finalVec, contextHandle);
}


// a - b 
LuaRef LuaVectorUtility::vec3_Subtract(LuaRef a, LuaRef b, LuaContextHandle contextHandle)
{
	vec3 vec1 = FromLuaTable<vec3>(a);
	vec3 vec2 = FromLuaTable<vec3>(b);
	vec3 finalVec = vec1 - vec2;
  return ToLuaTable(finalVec, contextHandle);
}

//mat4 identity
LuaRef LuaVectorUtility::mat4_CreateIdentity(LuaContextHandle contextHandle)
{
	mat4 empty;
	return ToLuaTable(empty, contextHandle);
}

// vec3 * constant
LuaRef LuaVectorUtility::vec3_ScalarMultiply(LuaRef value, float scalar, LuaContextHandle contextHandle)
{
	vec3 vec = FromLuaTable<vec3>(value);
  vec3 finalVec = vec * scalar;
	return ToLuaTable(finalVec, contextHandle);
}

bool LuaVectorUtility::vec3_Equals(LuaRef a, LuaRef b)
{
    if (FromLuaTable<vec3>(a) == FromLuaTable<vec3>(b))
      return true;
	return false;
}

LuaRef LuaVectorUtility::vec3_CreateEmpty(LuaContextHandle contextHandle)
{
	vec3 empty;
	return ToLuaTable(empty, contextHandle);
}



void LuaVectorUtility::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "vec3_Equals", vec3_Equals);

	pContext->ExposeFunction(luaAPIName, "vec3_CreateEmpty", vec3_CreateEmpty);

	pContext->ExposeFunction(luaAPIName, "vec3_Normalize", vec3_Normalize);
	pContext->ExposeFunction(luaAPIName, "vec3_Sum", vec3_Sum);
	pContext->ExposeFunction(luaAPIName, "vec3_Subtract", vec3_Subtract);
	pContext->ExposeFunction(luaAPIName, "mat4_CreateIdentity", mat4_CreateIdentity);
	pContext->ExposeFunction(luaAPIName, "vec3_ScalarMultiply", vec3_ScalarMultiply);
}