
/*

#pragma once
#include "types.h"
#Include "Map.h"
#include "ObjectInstanceAPI.h"


class Engine 
{
public:
  static Engine* Create();
  void ~Engine();
  void Initialise(int width, int height);
  //Screen manipulation
  void SetDimensions(int width, int height);
  void LoadModel(string modelName, string filePath);
  InstanceHandle CreateObjectInstance(string modelName);
  void BeginRender();
  void EndRender();

private:
  SDL_Window* m_screen;
  void Engine();
  LuaInstanceManager* m_instanceManager;

};
*/