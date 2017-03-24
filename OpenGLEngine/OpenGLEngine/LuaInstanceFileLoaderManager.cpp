#include "LuaInstanceFileLoaderManager.h"

static std::unordered_map<int, InstanceFileLoader*> m_instanceMap;
static int m_lastIndex = 0;

/// Returns handle to new object instance of given model name.
LoaderHandle LuaInstanceFileLoaderManager::AddNewInstance()
{

	InstanceFileLoader* newInstance;
	m_instanceMap.emplace(m_lastIndex, newInstance);
	m_lastIndex += 1;

	return m_lastIndex;
}

InstanceFileLoader * LuaInstanceFileLoaderManager::GetInstance(int instanceHandle)
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

void LuaInstanceFileLoaderManager::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "addNewInstance", AddNewInstance);
}