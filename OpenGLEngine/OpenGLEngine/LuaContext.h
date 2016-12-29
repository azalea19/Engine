#ifndef LuaContext_h__
#define LuaContext_h__

#include "Types.h"
#include "LuaBridge.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

typedef luabridge::lua_State LuaState;
typedef luabridge::LuaRef LuaRef;
typedef int LuaContextHandle;

class LuaContext
{
public:

  LuaContext(LuaContextHandle contextHandle, string const& entryScript);

  void Start();

  template<typename R, typename ...Args>
  void ExposeFunction(string const& functionName, R(*pFunction)(Args...));

  template<typename R, typename ...Args>
  void ExposeFunction(string const& namespaceName, string const& functionName, R(*pFunction)(Args...));

private:

  void Initialize();

  LuaState* m_pLuaState;
  LuaContextHandle m_contextHandle;
  string m_EntryScriptName;
};

template<typename R, typename ...Args>
void LuaContext::ExposeFunction(string const& functionName, R(*pFunction)(Args...))
{
  luabridge::getGlobalNamespace(m_pLuaState).addFunction(functionName.c_str(), pFunction);
}

template<typename R, typename ...Args>
void LuaContext::ExposeFunction(string const& namespaceName, string const& functionName, R(*pFunction)(Args...))
{
  luabridge::getGlobalNamespace(m_pLuaState)
    .beginNamespace(namespaceName.c_str())
    .addFunction(functionName.c_str(), pFunction)
    .endNamespace();
}
#endif // LuaContext_h__