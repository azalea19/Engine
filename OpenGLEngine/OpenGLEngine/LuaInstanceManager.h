#pragma once
#include <unordered_map>
#include "ObjectInstance.h"
#include "Singleton.h"
#include "ModelLibrary.h"
#include "LuaContext.h"
#include "LuaManager.h"
#include "ModelLibrary.h"

static class LuaInstanceManager : public Singleton<LuaInstanceManager>
{
//private:
	//static std::unordered_map<int,ObjectInstance*> m_instanceMap;
	//static int m_lastIndex;

public:
	/// Returns handle to new object instance of given model name.
	static int AddNewInstance(string const& modelName);

	static ObjectInstance* GetInstance(int instanceHandle);

	static void Expose(LuaContextHandle contextHandle, string luaAPIName);

};