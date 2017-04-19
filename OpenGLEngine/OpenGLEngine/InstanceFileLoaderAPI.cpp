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
	InstanceManager<InstanceFileLoader>().GetInstance().GetInst(handle)->LoadFile(filePath);
	//LuaInstanceFileLoaderManager().GetInstance(handle)->LoadFile(filePath);
}

InstanceHandle InstanceFileLoaderAPI::ReadFromLoadedFile(LoaderHandle handle, int index)
{
	return InstanceManager<InstanceFileLoader>().GetInstance().GetInst(handle)->ReadFromLoadedFile(index);
}

int InstanceFileLoaderAPI::GetFileLength(LoaderHandle handle)
{
	return InstanceManager<InstanceFileLoader>().GetInstance().GetInst(handle)->GetLength();
}