#pragma once
#include "MainRename.h"
class MainAPI
{
public:
	static void RenderBase();
	static void Initialise();
	static void UpdateBase();
	static void Expose(LuaContextHandle contextHandle, string luaAPIName);
};

