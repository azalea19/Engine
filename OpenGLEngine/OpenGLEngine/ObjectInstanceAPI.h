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
	static void SetTranslation(InstanceHandle instHandle, float in1, float in2, float in3);
	static void Expose(LuaContextHandle contextHandle, string luaAPIName);

};

