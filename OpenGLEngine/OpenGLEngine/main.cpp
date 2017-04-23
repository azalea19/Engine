#include "LuaManager.h"
#include "IEngine.h"
#include "GLEngine.h"
#include "DXEngine.h"
//#include "SDL.h"


int main(int argc, char **argv)
{
	LuaManager::Initialize();
	LuaManager::GetInstance().CreateContext("LuaScripts/Game.lua");
  //getchar();
	//SDL_SCANCODE_Q;
	//SDL_SCANCODE_Z;
  //return(0);
	getchar();
}