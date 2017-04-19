#ifndef MathAPI_h__
#define MathAPI_h__

#include "LuaContext.h"
#include "Types.h"
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
LuaRef ToLuaTable(vec3 value, LuaState luaState);

template<> mat4 FromLuaTable<mat4>(LuaRef value);
LuaRef ToLuaTable(mat4 value, LuaState luaState);


#endif // MathAPI_h__
