#include "LuaContext.h"
#include "LuaManager.h"

static void GetAPI(LuaContextHandle contextHandle, string luaAPIName, string apiName)
{
  LuaManager::GetInstance().ExposeAPI(contextHandle, luaAPIName, apiName);
}


static int Panic(LuaState* state)
{
  printf("some shit went down\n");
  getchar();
  return 0;
}

LuaContext::LuaContext(LuaContextHandle handle, string const& entryScript)
  : m_contextHandle(handle)
  , m_EntryScriptName(entryScript)
{
  m_pLuaState = luabridge::luaL_newstate();
  lua_atpanic(m_pLuaState, &Panic);
  luaL_openlibs(m_pLuaState);
  Initialize();
}

void LuaContext::Start()
{
  luaL_dofile(m_pLuaState, m_EntryScriptName.c_str());
}


void LuaContext::Initialize()
{
  ExposeFunction("GetAPI", GetAPI);

  getGlobalNamespace(m_pLuaState)
    .beginNamespace("context")
    .addVariable("handle", &m_contextHandle, false)
    .endNamespace();
}