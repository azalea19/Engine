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
	/// <summary>
	/// Elapseds time in milliseconds.
	/// </summary>
	/// <returns>float</returns>
	static float ElapsedTimeMs();

	/// <summary>
	/// Exposes the API
	/// </summary>
	/// <param name="contextHandle">The context handle.</param>
	/// <param name="luaAPIName">Name of the lua API.</param>
	static void TimeAPI::Expose(LuaContextHandle contextHandle, string luaAPIName);

};

