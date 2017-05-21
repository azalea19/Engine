
#pragma once
#include "Types.h"

#include "LuaContext.h"
#include "LuaManager.h"
#include <GL/glew.h>
#include "MathAPI.h"
#include <numeric>



/**
* @file LuaVectorUtility.h
* @Author Elizabeth Haynes
* @date   S1, 2017
* @brief API for handling vectors and mat4 in Lua
*
*/
class LuaVectorUtility
{
public:

  //vec3

	/// <summary>
	/// Vec3 normalize.
	/// </summary>
	/// <param name="value">The value to normaliz.</param>
	/// <param name="contextHandle">The context handle.</param>
	/// <returns>LuaRef</returns>
	static LuaRef LuaVectorUtility::vec3_Normalize(LuaRef value, LuaContextHandle contextHandle);
	

	static float LuaVectorUtility::vec3_DotProduct(LuaRef vec1, LuaRef vec2);


	/// <summary>
	/// Vec3 sum.
	/// </summary>
	/// <param name="a">Value 1 to sum.</param>
	/// <param name="b">Value 2 to sum.</param>
	/// <param name="contextHandle">The context handle.</param>
	/// <returns>LuaRef</returns>
	static LuaRef LuaVectorUtility::vec3_Sum(LuaRef a, LuaRef b, LuaContextHandle contextHandle);
	/// <summary>
	/// Vec3 subtract.
	/// </summary>
	/// <param name="a">Value 1 to subtract.</param>
	/// <param name="b">Value 2 to subtract.</param>
	/// <param name="contextHandle">The context handle.</param>
	/// <returns>LuaRef</returns>
	static LuaRef LuaVectorUtility::vec3_Subtract(LuaRef a, LuaRef b, LuaContextHandle contextHandle);
	/// <summary>
	/// Vec3 scalar multiply.
	/// </summary>
	/// <param name="value">The vec3 to multiply.</param>
	/// <param name="scalar">The scalar to multiply.</param>
	/// <param name="contextHandle">The context handle.</param>
	/// <returns>LuaRef</returns>
	static LuaRef LuaVectorUtility::vec3_ScalarMultiply(LuaRef value, float scalar, LuaContextHandle contextHandle);
	/// <summary>
	/// Vec3 multiply.
	/// </summary>
	/// <param name="vec1">A vec3 to multiply.</param>
	/// <param name="vec2">Second vec3 to multiply.</param>
	/// <param name="contextHandle">The context handle.</param>
	/// <returns>LuaRef</returns>
	static LuaRef LuaVectorUtility::vec3_Multiply(LuaRef vec1, LuaRef vec2, LuaContextHandle contextHandle);

	/// <summary>
	/// Vec3 create empty.
	/// </summary>
	/// <param name="contextHandle">The context handle.</param>
	/// <returns>LuaRef</returns>
	static LuaRef LuaVectorUtility::vec3_CreateEmpty(LuaContextHandle contextHandle);
	/// <summary>
	/// Vec3 equals.
	/// </summary>
	/// <param name="a">a.</param>
	/// <param name="b">The b.</param>
	/// <returns>bool</returns>
	static bool LuaVectorUtility::vec3_Equals(LuaRef a, LuaRef b);


  //mat4
	/// <summary>
	/// Mat4 create identity.
	/// </summary>
	/// <param name="contextHandle">The context handle.</param>
	/// <returns></returns>
	static LuaRef LuaVectorUtility::mat4_CreateIdentity(LuaContextHandle contextHandle);

	/// <summary>
	/// Exposes the API to lua.
	/// </summary>
	/// <param name="contextHandle">The context handle.</param>
	/// <param name="luaAPIName">Name of the lua API.</param>
	static void LuaVectorUtility::Expose(LuaContextHandle contextHandle, string luaAPIName);

};
