#pragma once
#include "LuaManager.h"
#include "InstanceFileLoader.h"
//#include "LuaInstanceManager.h"
#include "LuaInstanceFileLoaderManager.h"

class InstanceFileLoaderAPI
{
public:
	static void Expose(LuaContextHandle contextHandle, string luaAPIName);
	static void LoadFile(LoaderHandle handle, string fileName);
	static InstanceHandle ReadFromLoadedFile(LoaderHandle handle, int i);
	static int GetFileLength(LoaderHandle handle);

};

