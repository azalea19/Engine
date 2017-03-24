#pragma once
#include <unordered_map>
#include "ObjectInstance.h"
#include "Singleton.h"
#include "ModelLibrary.h"
#include "LuaContext.h"
#include "LuaManager.h"
#include "ModelLibrary.h"
#include "InstanceFileLoader.h"

typedef int LoaderHandle;

static class LuaInstanceFileLoaderManager : public Singleton<LuaInstanceFileLoaderManager>
{

public:
	
	/// Returns handle to new object instance of given model name.
	static LoaderHandle AddNewInstance();

	static InstanceFileLoader * GetInstance(int instanceHandle);


	static void Expose(LuaContextHandle contextHandle, string luaAPIName);

};