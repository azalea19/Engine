#pragma once
#include "Types.h"

#include "LuaContext.h"
#include "LuaManager.h"
#include <GL/glew.h>


class LuaVectorUtility
{
public:


	static LuaRef LuaVectorUtility::Normalize(float x, float y, float z);
	static void LuaVectorUtility::Expose(LuaContextHandle contextHandle, string luaAPIName);
	static LuaRef LuaVectorUtility::Add(float x1, float y1, float z1, float x2, float y2, float z2);

};

