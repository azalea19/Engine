#include "LuaManager.h"
#include "IEngine.h"
#include "GLEngine.h"
#include "DXEngine.h"
#include <iostream>


int main(int argc, char **argv)
{
	LuaManager::Initialize();
	LuaManager::GetInstance().CreateContext("../Assets/Scripts/Game.lua");
	std::cout << "Main has finished execution.\n" << std::endl;
	getchar();
}