#include "LuaVectorUtility.h"



LuaRef LuaVectorUtility::Normalize(float x, float y, float z)
{
	//float val[3];
	vec3 vec(x, y, z);
	vec = normalize(vec);
	float val [3] = { x,y,z };
	return val;
}


LuaRef LuaVectorUtility::Add(float x1, float y1, float z1, float x2, float y2, float z2)
{
	//float val[3];
	vec3 vec1(x1, y1, z1);
	vec3 vec2(x2, y2, z2);
	vec3 finalVec = vec1 + vec2;
	float val[3] = { finalVec.x,finalVec.y,finalVec.z };
	return val;
}

void LuaVectorUtility::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "addNewInstance", Normalize);
}