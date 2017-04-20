#include "DXEngine.h"
 
IEngine* DXEngine::Create()
{
  return new DXEngine();
}

void DXEngine::Initialise(int screenWidth, int screenHeight)
{
  throw std::logic_error("The method or operation is not implemented.");
}

void DXEngine::SetScreenDimensions()
{
  throw std::logic_error("The method or operation is not implemented.");
}

void DXEngine::BeginRender()
{
  throw std::logic_error("The method or operation is not implemented.");
}

void DXEngine::EndRender()
{
  throw std::logic_error("The method or operation is not implemented.");
}

bool DXEngine::BeginUpdate()
{
  throw std::logic_error("The method or operation is not implemented.");
}

void DXEngine::EndUpdate()
{
  throw std::logic_error("The method or operation is not implemented.");
}

DXEngine::DXEngine()
{

}

DXEngine::~DXEngine()
{

}

