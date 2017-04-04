#pragma once
#include "LuaManager.h"
#include "InstanceFileLoader.h"
#include "LuaInstanceFileLoaderManager.h"

class InstanceFileLoaderAPI
{
public:
	static void Expose(LuaContextHandle contextHandle, string luaAPIName);

	static void LoadFile(LoaderHandle handle, string fileName);

  //Creates a new instance and adds it to the Lua Instance Manager using the object data stored
  //in the object data vector at location i
	static InstanceHandle ReadFromLoadedFile(LoaderHandle handle, int i);

	static int GetFileLength(LoaderHandle handle);

};

