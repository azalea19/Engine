#include "EngineAPI.h"
#include "DXEngine.h"
#include "GLEngine.h"
#include "ShaderLibrary.h"
#include "ModelLibrary.h"
#include "InputManager.h"

std::unique_ptr<IEngine> EngineAPI::s_engine;

void EngineAPI::Create(int api)
{
  if (api == API_OPEN_GL)
    s_engine = std::unique_ptr<IEngine>(GLEngine::Create());
  else if (api == API_DIRECT_X)
    throw std::exception("API not supported.");
  else if (api == API_VULKAN)
    throw std::exception("API not supported.");
  else
    throw std::exception("API not supported.");
}

static void CreateShader(string const& name, string const& vertFilePath, string const& fragFilePath, std::vector<string> const& attributes, std::vector<string> const& uniforms)
{
  EngineAPI::GetEngine()->CreateShader(name, vertFilePath, fragFilePath, attributes, uniforms);
}

static void Initialise(int screenWidth, int screenHeight)
{
  EngineAPI::GetEngine()->Initialise(screenWidth, screenHeight);
  ShaderLibrary::InitShaderLibrary(EngineAPI::GetEngine());
  ModelLibrary::Initialise(EngineAPI::GetEngine());
  
  InputManager::GetInstance().Initialise(EngineAPI::GetEngine()->CreateInputHandler());
}

static bool BeginUpdate()
{
  return EngineAPI::GetEngine()->BeginUpdate();
}

static void EndUpdate()
{
  EngineAPI::GetEngine()->EndUpdate();
}


void EngineAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
  LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
  pContext->ExposeFunction(luaAPIName, "Create", Create);
  pContext->ExposeFunction(luaAPIName, "Initialise", Initialise);
  pContext->ExposeFunction(luaAPIName, "BeginUpdate", BeginUpdate);
  pContext->ExposeFunction(luaAPIName, "EndUpdate", EndUpdate);

}

IEngine* EngineAPI::GetEngine()
{
  return s_engine.get();
}
