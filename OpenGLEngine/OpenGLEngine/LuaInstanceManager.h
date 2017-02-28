#pragma once
#include <unordered_map>
#include "ObjectInstance.h"
#include "Singleton.h"
#include "ModelLibrary.h"

class LuaInstanceManager : public Singleton<LuaInstanceManager>
{
private:
	std::unordered_map<int,ObjectInstance*> m_instanceMap;
	int m_lastIndex = 0;

public:

	/// Returns handle to new object instance of given model name.
	int AddNewInstance(string const& modelName);

	ObjectInstance* GetInstance(int instanceHandle);

};