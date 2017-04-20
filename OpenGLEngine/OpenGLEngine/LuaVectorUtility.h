
#pragma once
#include "Types.h"

#include "LuaContext.h"
#include "LuaManager.h"
#include <GL/glew.h>
#include "MathAPI.h"

/// API for handling vec3 in Lua
class LuaVectorUtility
{
public:


	static LuaRef LuaVectorUtility::Normalize(float x, float y, float z);
	static LuaRef LuaVectorUtility::AddVector(LuaRef a, LuaRef b);
	static LuaRef LuaVectorUtility::SubtractVector(LuaRef a, LuaRef b);
	static LuaRef LuaVectorUtility::GetEmptyMat4();


	static LuaRef LuaVectorUtility::MultiplyFloat(float x, float y, float z, float flt);

	static void LuaVectorUtility::Expose(LuaContextHandle contextHandle, string luaAPIName);


};
