#pragma once

#include "LuaContext.h"
#include "LuaManager.h"
class TimeAPI
{
public:
	/// Elapsed time in milliseconds
	static float ElapsedTimeMs();
	static void TimeAPI::Expose(LuaContextHandle contextHandle, string luaAPIName);

};

