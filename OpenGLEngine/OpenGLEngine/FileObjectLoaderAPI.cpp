#include "FileObjectLoaderAPI.h"


static InstanceFileLoader loader;

void InstanceFileLoaderAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "addModel", ReadFile);
}

void InstanceFileLoaderAPI::ReadFile(string filePath)
{
	loader.LoadFile(filePath);
}

InstanceHandle InstanceFileLoaderAPI::ReadFromLoadedFile(int index)
{
	return loader.ReadFromLoadedFile(index);
}
