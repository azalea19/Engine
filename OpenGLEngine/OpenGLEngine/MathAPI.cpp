#include "MathAPI.h"
//#include <glm/gtc/type_ptr.hpp>

static void ExposeVec3(LuaContext* pContext, string const& luaAPIName)
{
  pContext->AddClass<vec3>(luaAPIName, "vec3");
  pContext->AddClassDataMember<vec3>(luaAPIName, "vec3", "x", &vec3::x);
  pContext->AddClassDataMember<vec3>(luaAPIName, "vec3", "y", &vec3::y);
  pContext->AddClassDataMember<vec3>(luaAPIName, "vec3", "z", &vec3::z);
  pContext->AddClassConstructor<vec3, void(*) (void)>(luaAPIName, "vec3");
}

LuaRef ToLuaTable(vec3 value, LuaContextHandle contextHandle)
{
  LuaRef table = newTable(LuaManager::GetInstance().GetContext(contextHandle)->GetLuaState());
  table["x"] = value.x;
  table["y"] = value.y;
  table["z"] = value.z;

  return table;
}


LuaRef ToLuaTable(mat4 value, LuaContextHandle contextHandle)
{
  LuaRef table = newTable(LuaManager::GetInstance().GetContext(contextHandle)->GetLuaState());
 
  const float *pSource = (const float*)glm::value_ptr(value);
 

  for (int i = 0; i < 16; i++)
  {
	 table[i + i] = pSource[i];
  }

  return table;
 
}

template<>
vec3 FromLuaTable<vec3>(LuaRef value)
{
  vec3 result;
  result.x = float(value["x"]);
  result.y = float(value["y"]);
  result.z = float(value["z"]);
  return result;
}

template<> mat4 FromLuaTable<mat4>(LuaRef value)
{
  float result[16];

  for (int i = 1; i <= 16; i++)
  {
    result[i - 1] = value[i];
  }
  return glm::make_mat4(result);
}


void MathAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
  LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
  ExposeVec3(pContext, luaAPIName);
}


