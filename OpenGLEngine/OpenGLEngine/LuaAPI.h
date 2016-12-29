#ifndef LuaAPI_h__
#define LuaAPI_h__

#include "LuaManager.h"

typedef void(*LuaAPIExposeFunc)(LuaContextHandle contextHandle, string luaAPIName);
#endif // LuaAPI_h__