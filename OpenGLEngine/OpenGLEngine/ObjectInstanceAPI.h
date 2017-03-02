#pragma once
#include "LuaContext.h"
#include "LuaInstanceManager.h"
#include "LuaManager.h"
#include "ShaderLibrary.h"
#include "MPlayer.h"
#include "MCamera.h"

class ObjectInstanceAPI
{
public:
	static ObjectInstance * GetInstance(int instHandle);
	static void SetTranslation(int instHandle, vec3 const& translation);
	static void TestRender(int instHandle);

	static void Expose(LuaContextHandle contextHandle, string luaAPIName);

};

