#include "InstanceFileLoaderAPI.h"


static InstanceFileLoader loader;

void InstanceFileLoaderAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "loadFile", LoadFile);
	pContext->ExposeFunction(luaAPIName, "readFromLoadedFile", ReadFromLoadedFile);
	pContext->ExposeFunction(luaAPIName, "getFileLength", GetFileLength);

}

void InstanceFileLoaderAPI::LoadFile(LoaderHandle handle, string filePath)
{
	LuaInstanceFileLoaderManager().GetInstance(handle)->LoadFile(filePath);
}

InstanceHandle InstanceFileLoaderAPI::ReadFromLoadedFile(LoaderHandle handle, int index)
{
	return LuaInstanceFileLoaderManager().GetInstance(handle)->ReadFromLoadedFile(index);
}

int InstanceFileLoaderAPI::GetFileLength(LoaderHandle handle)
{
	return LuaInstanceFileLoaderManager().GetInstance(handle)->GetLength();
}