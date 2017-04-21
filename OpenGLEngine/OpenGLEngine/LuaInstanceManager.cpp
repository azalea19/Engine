#include "LuaInstanceManager.h"


static std::unordered_map<int, ObjectInstance*> m_instanceMap;

static int m_lastIndex = 0;

/// Returns handle to new object instance of given model name.
InstanceHandle LuaInstanceManager::AddNewInstance(string const& modelName)
{

	ObjectInstance* newInstance = ModelLibrary::GetInstance().GetObjectInstance(modelName);
	m_instanceMap.emplace(m_lastIndex, newInstance);
	m_lastIndex += 1;
	
	return m_lastIndex-1;
}

ObjectInstance * LuaInstanceManager::GetInstance(int instanceHandle)
{

	auto got = m_instanceMap.find(instanceHandle);

	if (got == m_instanceMap.end())
	{
		printf("Instance with name %n not found.", instanceHandle);
		ObjectInstance * nullInst;
		return nullInst;
	}
	
	return got->second;
}

void LuaInstanceManager::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "addNewInstance", AddNewInstance);
}