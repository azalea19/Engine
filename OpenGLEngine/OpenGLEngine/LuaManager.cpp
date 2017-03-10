#include "LuaManager.h"
#include "PrintAPI.h"
#include "ObjectInstanceAPI.h"
#include "LuaInstanceManager.h"
#include "ModelLibraryAPI.h"
#include "RenderManagerAPI.h"
#include "MainAPI.h"

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
  luaManager.AddAPI("objectInstanceAPI", ObjectInstanceAPI::Expose);
  luaManager.AddAPI("luaInstanceManager", LuaInstanceManager::Expose);
  luaManager.AddAPI("modelLibraryAPI", ModelLibraryAPI::Expose);
  luaManager.AddAPI("renderManagerAPI", RenderManagerAPI::Expose);
  luaManager.AddAPI("mainAPI", MainAPI::Expose);
}

void LuaManager::AddAPI(string apiName, LuaAPIExposeFunc exposeFunc)
{
  m_apiExposeFunctions.emplace(apiName, exposeFunc);
}

LuaContextHandle LuaManager::ReserveContextHandle()
{
  return nextHandle++;
}
