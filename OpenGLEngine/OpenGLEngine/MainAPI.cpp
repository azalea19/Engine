#include "MainAPI.h"
void MainAPI::RenderBase()
{
	MainRename::Render();
}

void MainAPI::Initialise()
{

	MainRename::InitSDL();

	MainRename::MyInit();
}

void MainAPI::UpdateBase()
{
	MainRename::Update();
}
void MainAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "initialise", Initialise);
	pContext->ExposeFunction(luaAPIName, "render", RenderBase);
	pContext->ExposeFunction(luaAPIName, "update", UpdateBase);
}