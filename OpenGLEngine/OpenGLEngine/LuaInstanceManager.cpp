#include "LuaInstanceManager.h"


static std::unordered_map<int, ObjectInstance*> m_instanceMap;

static int m_lastIndex = 0;

/// Returns handle to new object instance of given model name.
int LuaInstanceManager::AddNewInstance(string const& modelName)
{

	ObjectInstance* newInstance = ModelLibrary::GetInstance().GetObjectInstance(modelName);
	m_instanceMap.emplace(m_lastIndex, newInstance);
	m_lastIndex += 1;

	//Liz once you have the new instance of the mode and its unique handle
	//you need to add the new key value pair to the map 
	//use emplace, insert is trash
	//i.e. myMap.emplace(myKey, myValue)

	
	return m_lastIndex;
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