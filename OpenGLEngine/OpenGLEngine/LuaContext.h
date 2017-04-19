#ifndef LuaContext_h__
#define LuaContext_h__

#include "Types.h"
#include "LuaBridge.h"


/**
* @file LuaContext.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief 
*
*/


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

  /// <summary>
  /// Initializes a new instance of the <see cref="LuaContext"/> class.
  /// </summary>
  /// <param name="contextHandle">The context handle.</param>
  /// <param name="entryScript">The entry script.</param>
  LuaContext(LuaContextHandle contextHandle, string const& entryScript);

  void Start();

  template<typename R, typename ...Args>
  void ExposeFunction(string const& functionName, R(*pFunction)(Args...));

  template<typename R, typename ...Args>
  void ExposeFunction(string const& namespaceName, string const& functionName, R(*pFunction)(Args...));

  template<typename T>
  void AddClass(string const& luaAPIName, string const& className);

  template<typename ClassType, typename DataType>
  void AddClassDataMember(string const& luaAPIName, string const& className, string const& memberName, DataType dataMember);

  template<typename ClassType, typename FunctionType>
  void AddClassFunction(string const& luaAPIName, string const& className, string const& functionName, FunctionType* function);

  template<typename ClassType, typename ConstructorType>
  void AddClassConstructor(string const& luaAPIName, string const& className);

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

template<typename T>
void LuaContext::AddClass(string const& luaAPIName, string const& className)
{
  getGlobalNamespace(m_pLuaState).beginNamespace(luaAPIName.c_str()).beginClass<T>(className.c_str()).endClass().endNamespace();
}


template<typename ClassType, typename DataType>
void LuaContext::AddClassDataMember(string const& luaAPIName, string const& className, string const& memberName, DataType dataMember)
{
  getGlobalNamespace(m_pLuaState)
    .beginNamespace(luaAPIName.c_str())
    .beginClass<ClassType>(className.c_str())
    .addData(memberName.c_str(), dataMember)
    .endClass()
    .endNamespace();
}


template<typename ClassType, typename FunctionType>
void LuaContext::AddClassFunction(string const& luaAPIName, string const& className, string const& functionName, FunctionType* function)
{
  getGlobalNamespace(m_pLuaState)
    .beginNamespace(luaAPIName.c_str())
    .beginClass<ClassType>(className.c_str())
    .addFunction(functionName.c_str(), function)
    .endClass()
    .endNamespace();
}

template<typename ClassType, typename ConstructorType>
void LuaContext::AddClassConstructor(string const& luaAPIName, string const& className)
{
  getGlobalNamespace(m_pLuaState)
    .beginNamespace(luaAPIName.c_str())
    .beginClass<ClassType>(className.c_str())
    .addConstructor<ConstructorType>()
    .endClass()
    .endNamespace();
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