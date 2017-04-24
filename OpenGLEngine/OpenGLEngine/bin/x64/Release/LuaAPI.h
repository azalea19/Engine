#ifndef LuaAPI_h__
#define LuaAPI_h__

#include "LuaManager.h"

/**
* @file LuaAPI.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief
*
*/

typedef void(*LuaAPIExposeFunc)(LuaContextHandle contextHandle, string luaAPIName);

#endif // LuaAPI_h__