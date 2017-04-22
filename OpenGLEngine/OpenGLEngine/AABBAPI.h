#pragma once

#include "LuaBridge.h"

#include "LuaContext.h"
#include "LuaManager.h"
#include "Types.h"
#include "LuaObjectInstanceManager.h"
#include "MathAPI.h"

/**
* @file   AABBAPI.h
* @Author Elizabeth Haynes
* @date   S1, 2017
* @brief  Lua API for getting Axis Aligned Bounding Boxes
*/


class AABBAPI
{
public:

	static LuaRef GetAABB(int handle, LuaContextHandle cHandle);
	static LuaRef Move(LuaRef bbox, LuaRef oldPos, LuaRef newPos, LuaContextHandle cHandle);

	static void Expose(LuaContextHandle contextHandle, string luaAPIName);

private:

	//static std::vector<vec3> GetMin(int instHandle);
	//static void GetMax(int instHandle);

};

