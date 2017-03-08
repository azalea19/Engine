#pragma once
#include "LuaContext.h"
#include "LuaInstanceManager.h"
#include "LuaManager.h"
#include "ShaderLibrary.h"
#include "MPlayer.h"
#include "MCamera.h"

typedef int InstanceHandle;

class ObjectInstanceAPI
{
public:
	static ObjectInstance * GetInstance(InstanceHandle instHandle);
	static void SetTranslation(InstanceHandle instHandle, vec3 const& translation);
	static void TestRender(InstanceHandle instHandle);

	static void Expose(LuaContextHandle contextHandle, string luaAPIName);

};

