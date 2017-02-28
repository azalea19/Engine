#pragma once
#include "LuaContext.h"
#include "LuaInstanceManager.h"

class ObjectInstanceAPI
{
public:
	ObjectInstanceAPI();
	~ObjectInstanceAPI();

	void Expose(LuaContextHandle contextHandle, string luaAPIName);

};

