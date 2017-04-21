#ifndef MathAPI_h__
#define MathAPI_h__

#include "LuaBridge.h"

#include "LuaContext.h"
#include "LuaManager.h"
#include "Types.h"

class MathAPI
{
public:

  static void Expose(LuaContextHandle contextHandle, string luaAPIName);
};

template<typename T>
T FromLuaTable(LuaRef value)
{
  static_assert(false, "FromLuaTable is not defined for this type.");
}

template<> vec3 FromLuaTable<vec3>(LuaRef value);
LuaRef ToLuaTable(vec3 value, LuaContextHandle contextHandle);

template<> mat4 FromLuaTable<mat4>(LuaRef value);
LuaRef ToLuaTable(mat4 value, LuaContextHandle contextHandle);


#endif // MathAPI_h__
