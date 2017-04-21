#include "InstanceManagerAPI.h"

/*
/// Returns handle to new object instance of given model name.
LoaderHandle InstanceManagerAPI::AddNewInstance()
{

	InstanceFileLoader* newInstance = new InstanceFileLoader();
	m_instanceMap.emplace(m_lastIndex, newInstance);
	m_lastIndex += 1;

	return m_lastIndex - 1;
}

InstanceFileLoader * InstanceManagerAPI::GetInstance(int instanceHandle)
{

	auto got = m_instanceMap.find(instanceHandle);

	if (got == m_instanceMap.end())
	{
		printf("Instance with name %n not found.", instanceHandle);
		InstanceFileLoader * nullInst;
		return nullInst;
	}

	return got->second;
}

void LuaInstanceFileLoaderManager::Expose(InstanceManagerAPI contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "addNewInstance", AddNewInstance);


}
*/
