#include "LuaInstanceFileLoaderManager.h"

LoaderHandle LuaInstanceFileLoaderManager::AddNewInstance()
{
	return InstanceManager<InstanceFileLoader>().GetInstance().AddNewInstance();
}

InstanceFileLoader * LuaInstanceFileLoaderManager::GetInstance(int instanceHandle)
{
	return InstanceManager<InstanceFileLoader>().GetInstance().GetInst(instanceHandle);
}

void LuaInstanceFileLoaderManager::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "addNewInstance", AddNewInstance);
}