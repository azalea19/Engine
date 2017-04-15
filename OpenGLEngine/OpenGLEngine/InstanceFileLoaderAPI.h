#pragma once
#include "LuaManager.h"
#include "InstanceFileLoader.h"
//#include "LuaInstanceManager.h"
#include "LuaInstanceFileLoaderManager.h"

class InstanceFileLoaderAPI
{
public:
	static void Expose(LuaContextHandle contextHandle, string luaAPIName);
	static void LoadFile(InstanceHandle handle, string fileName);
	static InstanceHandle ReadFromLoadedFile(InstanceHandle handle, int i);
	static int GetFileLength(InstanceHandle handle);

};

