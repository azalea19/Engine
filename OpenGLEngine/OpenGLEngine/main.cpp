 
#include "LuaManager.h"
#include "MainAPI.h"


int main(int argc, char **argv)
{
	LuaManager::Initialize();
	//MainAPI::Initialise();
	LuaManager::GetInstance().CreateContext("LuaScripts/Game.lua");
	/*
	SDL_SCANCODE_W 26;
	SDL_SCANCODE_S 22;
	SDL_SCANCODE_A 4;
	SDL_SCANCODE_D 7;
	*/
		
  return(0);
}