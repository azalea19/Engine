#pragma once
#include <unordered_map>
#include "Singleton.h"
#include "LuaContext.h"
#include "LuaManager.h"

#include "MCamera.h"

typedef int InstanceHandle;


static class MCameraInstanceManager : public Singleton<MCameraInstanceManager>
{
	//private:
	//static std::unordered_map<int,ObjectInstance*> m_instanceMap;
	//static int m_lastIndex;

public:
	/// Returns handle to new object instance of given model name.
	static InstanceHandle AddNewInstance(string const& modelName);

	static MCamera* GetInstance(int instanceHandle);

	static void Expose(LuaContextHandle contextHandle, string luaAPIName);

};
