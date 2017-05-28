#include "LuaManager.h"
#include "IEngine.h"
#include "GLEngine.h"
#include "DXEngine.h"
#include <iostream>


int main(int argc, char **argv)
{
<<<<<<< HEAD
	LuaManager::Initialize();
	LuaManager::GetInstance().CreateContext("../Assets/Scripts/Game.lua");
	std::cout << "Main has finished execution.\n" << std::endl;
	getchar();
=======
  LuaManager::Initialize();
  LuaManager::GetInstance().CreateContext("../Assets/Scripts/NewGame.lua");
  getchar();
>>>>>>> 36947cce270eff9264ef4a438bd106f1a7a57b9e
}