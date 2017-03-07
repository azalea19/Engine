#pragma once

#include "LuaManager.h"
#include "MainAPI.h"


int main(int argc, char **argv)
{
	LuaManager::Initialize();
	//MainAPI::Initialise();
	LuaManager::GetInstance().CreateContext("Game.lua");
  return(0);
}
