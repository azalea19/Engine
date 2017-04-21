#pragma once

#include "LuaContext.h"
#include "LuaManager.h"


/**
* @file   InputManagerAPI.h
* @Author Elizabeth Haynes
* @date   S1, 2017
* @brief  Lua API for C++ time.
*
*/
class TimeAPI
{
public:
	/// Elapsed time in milliseconds
	static float ElapsedTimeMs();
	static void TimeAPI::Expose(LuaContextHandle contextHandle, string luaAPIName);

};

