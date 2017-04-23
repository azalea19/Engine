#include "LuaObjectInstanceManager.h"
#include "MCamera.h"
#include "LuaInstanceManager.h"

static std::unordered_map<int, ObjectInstance*> m_instanceMap;

static int m_lastIndex = 0;

/// Returns handle to new object instance of given model name.

InstanceHandle LuaObjectInstanceManager::AddNewInstance(string const& modelName)
{

	ObjectInstance* newInstance = ModelLibrary::GetInstance().GetObjectInstance(modelName);
	m_instanceMap.emplace(m_lastIndex, newInstance);
	m_lastIndex += 1;
	
	return m_lastIndex-1;
}

void LuaObjectInstanceManager::DeleteInstance(int instanceHandle)
{

	auto got = m_instanceMap.find(instanceHandle);

	if (got == m_instanceMap.end())
	{
		printf("Instance with name %n not found.", instanceHandle);
	}
	else {
		m_instanceMap.erase(instanceHandle);
	}

}

ObjectInstance * LuaObjectInstanceManager::GetInstance(int instanceHandle)
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

void LuaObjectInstanceManager::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "addNewInstance", AddNewInstance);
	pContext->ExposeFunction(luaAPIName, "deleteInstance", DeleteInstance);
}