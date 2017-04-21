
#pragma once
#include "Types.h"

#include "LuaContext.h"
#include "LuaManager.h"
#include <GL/glew.h>
#include "MathAPI.h"

/// API for handling vectors in Lua
class LuaVectorUtility
{
public:

  //vec3
	static LuaRef LuaVectorUtility::vec3_Normalize(LuaRef value, LuaContextHandle contextHandle);
	static LuaRef LuaVectorUtility::vec3_Sum(LuaRef a, LuaRef b, LuaContextHandle contextHandle);
	static LuaRef LuaVectorUtility::vec3_Subtract(LuaRef a, LuaRef b, LuaContextHandle contextHandle);
	static LuaRef LuaVectorUtility::vec3_ScalarMultiply(LuaRef value, float scalar, LuaContextHandle contextHandle);
	static LuaRef LuaVectorUtility::vec3_CreateEmpty(LuaContextHandle contextHandle);
	static bool LuaVectorUtility::vec3_Equals(LuaRef a, LuaRef b);


  //mat4
	static LuaRef LuaVectorUtility::mat4_CreateIdentity(LuaContextHandle contextHandle);

	static void LuaVectorUtility::Expose(LuaContextHandle contextHandle, string luaAPIName);

};
