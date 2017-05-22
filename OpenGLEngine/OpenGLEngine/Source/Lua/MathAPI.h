#ifndef MathAPI_h__
#define MathAPI_h__

#include "LuaBridge.h"

#include "LuaContext.h"
#include "LuaManager.h"
#include "Types.h"
#include "GeometricPrimitives.h"


/**
* @file   InputManagerAPI.h
* @Author Maddie Topaz
* @date   S1, 2017
* @brief  Lua API for math functions
*
*/
class MathAPI
{
public:

  static void Expose(LuaContextHandle contextHandle, string luaAPIName);
};

template<typename T>
/// <summary>
/// Gets Type return from the lua table.
/// </summary>
/// <param name="value">The value.</param>
/// <returns></returns>
T FromLuaTable(LuaRef value)
{
  static_assert(false, "FromLuaTable is not defined for this type.");
}

/// <summary>
/// Gets vec3 return from the lua table.
/// </summary>
/// <param name="value">The value.</param>
/// <returns>vec3</returns>
template<> vec3 FromLuaTable<vec3>(LuaRef value);

template<> vec2 FromLuaTable<vec2>(LuaRef value);


LuaRef ToLuaTable(vec3 value, LuaContextHandle contextHandle);


LuaRef ToLuaTable(mAABB value, LuaContextHandle contextHandle);


/// <summary>
/// Gets mat4 return from the lua table.
/// </summary>
/// <param name="value">The value.</param>
/// <returns>mat4</returns>
template<> mat4 FromLuaTable<mat4>(LuaRef value);

/// <summary>
/// Gets mAABB return from the lua table.
/// </summary>
/// <param name="value">The value.</param>
/// <returns>mAABB</returns>
template<> mAABB FromLuaTable<mAABB>(LuaRef value);

/// <summary>
/// Gets mRay return from the lua table.
/// </summary>
/// <param name="value">The value.</param>
/// <returns>mRay</returns>
template<> mRay FromLuaTable<mRay>(LuaRef value);


/// <summary>
/// Converts mat4 to lua table
/// </summary>
/// <param name="value">The value.</param>
/// <param name="contextHandle">The context handle.</param>
/// <returns>LuaRef</returns>
LuaRef ToLuaTable(mat4 value, LuaContextHandle contextHandle);
/// <summary>
/// Converts vector of floats to 2D lua table
/// </summary>
/// <param name="data">Vector of float.</param>
/// <param name="width">Desired width.</param>
/// <param name="height">Desired height.</param>
/// <param name="contextHandle">The context handle.</param>
/// <returns>LuaRef</returns>
LuaRef ToLuaTable(std::vector<float> data, int width, int height, LuaContextHandle contextHandle);

#endif // MathAPI_h__
