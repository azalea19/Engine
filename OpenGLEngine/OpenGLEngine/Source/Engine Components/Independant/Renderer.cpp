#include "Renderer.h"


void Renderer::BeginRender() const
{
  renderer->BeginRender();
}

void Renderer::EndRender() const
{
  renderer->EndRender();
}

void Renderer::Present(int camID) const
{
  renderer->Present(camID);
}

void Renderer::SetFillMode(int fillMode) const
{
  renderer->SetFillMode(fillMode);
}

void Renderer::RenderObject(int camID, float time, int instanceHandle, int lightingApplied) const
{
  renderer->RenderObject(camID, time, instanceHandle, lightingApplied);
}

void Renderer::Initialise(IRenderManager* renderManager)
{
  renderer = std::unique_ptr<IRenderManager>(renderManager);
  renderer->Initialise();
}
