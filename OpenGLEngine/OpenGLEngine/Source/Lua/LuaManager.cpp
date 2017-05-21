#include "LuaManager.h"
#include "PrintAPI.h"
#include "ObjectInstanceAPI.h"
#include "LuaInstanceManager.h"
#include "ModelLibraryAPI.h"
#include "RenderManagerAPI.h"
#include "MainAPI.h"
#include "InputManagerAPI.h"
#include "LuaVectorUtility.h"
#include "CameraAPI.h"
#include "EngineAPI.h"
#include "TimeAPI.h"
#include "TerrainAPI.h"
#include "AABBAPI.h"
#include "IslandCollisionAPI.h"
#include "LuaDisplay2DAPI.h"
#include "CollisionAPI.h"

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
  luaManager.AddAPI("luaObjectInstanceManager", LuaObjectInstanceManager::Expose);
  luaManager.AddAPI("modelLibraryAPI", ModelLibraryAPI::Expose);
  luaManager.AddAPI("renderManagerAPI", RenderManagerAPI::Expose);
  luaManager.AddAPI("inputManagerAPI", InputManagerAPI::Expose);
  luaManager.AddAPI("luaVectorUtility", LuaVectorUtility::Expose);
  luaManager.AddAPI("engineAPI", EngineAPI::Expose);
  luaManager.AddAPI("cameraAPI", CameraAPI::Expose);
  luaManager.AddAPI("timeAPI", TimeAPI::Expose);
  luaManager.AddAPI("terrainAPI", TerrainAPI::Expose);
  luaManager.AddAPI("AABBAPI", AABBAPI::Expose);
  luaManager.AddAPI("islandCollisionAPI", IslandCollisionAPI::Expose);
  luaManager.AddAPI("display2DAPI", LuaDisplay2DAPI::Expose);
  luaManager.AddAPI("collisionAPI", CollisionAPI::Expose);




}

void LuaManager::AddAPI(string apiName, LuaAPIExposeFunc exposeFunc)
{
  m_apiExposeFunctions.emplace(apiName, exposeFunc);
}

LuaContextHandle LuaManager::ReserveContextHandle()
{
  return nextHandle++;
}
