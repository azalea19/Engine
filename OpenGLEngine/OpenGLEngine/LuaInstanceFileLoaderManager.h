#pragma once
#include "Singleton.h"
#include "InstanceFileLoader.h"
#include "InstanceManager.h"

typedef int LoaderHandle;

static class LuaInstanceFileLoaderManager : public Singleton<LuaInstanceFileLoaderManager>
{

public:
	
	/// Returns handle to new object instance of given model name.
	static LoaderHandle AddNewInstance();

	static InstanceFileLoader * GetInstance(int instanceHandle);


	static void Expose(LuaContextHandle contextHandle, string luaAPIName);

};