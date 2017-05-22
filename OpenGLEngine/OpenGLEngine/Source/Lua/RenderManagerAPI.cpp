
#include "RenderManagerAPI.h"
#include "LuaObjectInstanceManager.h"
#include "GBuffer.h"
#include "EngineAPI.h"
#include "Renderer.h"


void RenderManagerAPI::RenderObject(int camID, float time, int instanceHandle, int lightingApplied)
{
  Renderer::GetInstance().RenderObject(camID, time, instanceHandle, lightingApplied);
}

void RenderManagerAPI::BeginRender()
{
  Renderer::GetInstance().BeginRender();
}

void RenderManagerAPI::EndRender()
{
  Renderer::GetInstance().EndRender();
}


void RenderManagerAPI::Present(int camID)
{
  Renderer::GetInstance().Present(camID);
}

void RenderManagerAPI::SetFillMode(int fillMode)
{
  Renderer::GetInstance().SetFillMode(fillMode);
}


void RenderManagerAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
  LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
  pContext->ExposeFunction(luaAPIName, "renderObject", RenderObject);
  pContext->ExposeFunction(luaAPIName, "present", Present);
  pContext->ExposeFunction(luaAPIName, "beginRender", BeginRender);
  pContext->ExposeFunction(luaAPIName, "endRender", EndRender);
  pContext->ExposeFunction(luaAPIName, "setFillMode", SetFillMode);
}

