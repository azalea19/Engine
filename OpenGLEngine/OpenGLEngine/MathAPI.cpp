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

LuaRef ToLuaTable(vec3 value, LuaState* luaState)
{
  LuaRef table = newTable(luaState);
  table["x"] = value.x;
  table["y"] = value.y;
  table["z"] = value.z;

  return table;
}


LuaRef ToLuaTable(vec3 value)
{
	LuaState * state = LuaManager::GetInstance().GetContext(0)->GetLuaState();
	return ToLuaTable(value, state);
}


LuaRef ToLuaTable(mat4 value, LuaState* luaState)
{
  LuaRef table = newTable(luaState);

  //table["x"] = "a";

  const float *pSource = (const float*)glm::value_ptr(value);
 

  for (int i = 0; i < 16; i++)
  {
	 table[i + i] = pSource[i];
  }

  return table;
}



LuaRef ToLuaTable(mat4 value)
{
	LuaState * state = LuaManager::GetInstance().GetContext(0)->GetLuaState();

	return ToLuaTable(value, state);
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
	float vals[16];
  for (int i = 1; i <= 16; i++)
  {

	  LuaRef val = value[i];
	  //string str = val.to
	  float num = lua_tonumber(val,1);
	  vals[i - 1] = num;
  }

  return glm::make_mat4(vals);
}

void MathAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
  LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
  ExposeVec3(pContext, luaAPIName);
}


