#include "LuaManager.h"
#include "IEngine.h"
#include "GLEngine.h"
#include "DXEngine.h"


int main(int argc, char **argv)
{

  LuaManager::Initialize();

  LuaManager::GetInstance().CreateContext("LuaScripts/Engine.lua");
  
  return(0);
}