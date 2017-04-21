#include "EngineAPI.h"
#include "DXEngine.h"
#include "GLEngine.h"
#include "ShaderLibrary.h"

/// <summary>
/// The s engine{CC2D43FA-BBC4-448A-9D0B-7B57ADF2655C}
/// </summary>
IEngine* EngineAPI::s_engine;

static void Create(int graphicsFlag)
{
  if (graphicsFlag == API_OPEN_GL)
  {
    EngineAPI::s_engine = GLEngine::Create();
  }
  if (graphicsFlag == API_DIRECT_X)
  {
    EngineAPI::s_engine = DXEngine::Create();
  }
}

static void CreateShader(string const& name, string const& vertFilePath, string const& fragFilePath, std::vector<string> const& attributes, std::vector<string> const& uniforms)
{
  EngineAPI::s_engine->CreateShader(name, vertFilePath, fragFilePath, attributes, uniforms);
}


static void Initialise(int screenWidth, int screenHeight)
{
  EngineAPI::s_engine->Initialise(screenWidth, screenHeight);
  ShaderLibrary::InitShaderLibrary(EngineAPI::s_engine);
}

static bool BeginUpdate()
{
  return EngineAPI::s_engine->BeginUpdate();
}

static void EndUpdate()
{
  EngineAPI::s_engine->EndUpdate();
}

static void BeginRender()
{
  EngineAPI::s_engine->BeginRender();
}

static void EndRender()
{
  EngineAPI::s_engine->EndRender();
}

void EngineAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
  LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
  pContext->ExposeFunction(luaAPIName, "Create", Create);
  pContext->ExposeFunction(luaAPIName, "Initialise", Initialise);
  pContext->ExposeFunction(luaAPIName, "BeginUpdate", BeginUpdate);
  pContext->ExposeFunction(luaAPIName, "EndUpdate", EndUpdate);
  pContext->ExposeFunction(luaAPIName, "BeginRender", BeginRender);
  pContext->ExposeFunction(luaAPIName, "EndRender", EndRender);
}
