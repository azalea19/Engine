#pragma once

#include "LuaContext.h"
#include "LuaManager.h"
#include "ModelLibrary.h"

class ModelLibraryAPI
{
public:

	static void AddModel(string const& name, string const& path, bool normalized);
	static void Expose(LuaContextHandle contextHandle, string luaAPIName);
};

