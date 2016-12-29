#include "LuaManager.h"
#include "PrintAPI.h"

LuaContext* LuaManager::GetContext(LuaContextHandle contextHandle)
{
  return m_contexts.at(contextHandle);
}

LuaContextHandle LuaManager::CreateContext(string scriptPath)
{
  LuaContextHandle handle = ReserveContextHandle();
  LuaContext* context = new LuaContext(handle, scriptPath);
  m_contexts.emplace(handle, context);
  context->Start();
  return handle;
}

void LuaManager::ExposeAPI(LuaContextHandle contextHandle, string luaAPIName, string apiName)
{
  LuaAPIExposeFunc exposeFunc = m_apiExposeFunctions.at(apiName);
  exposeFunc(contextHandle, luaAPIName);
}

void LuaManager::Initialize()
{
  LuaManager& luaManager = LuaManager::GetInstance();
  luaManager.AddAPI("printAPI", PrintAPI::Expose);
}

void LuaManager::AddAPI(string apiName, LuaAPIExposeFunc exposeFunc)
{
  m_apiExposeFunctions.emplace(apiName, exposeFunc);
}

LuaContextHandle LuaManager::ReserveContextHandle()
{
  return nextHandle++;
}
