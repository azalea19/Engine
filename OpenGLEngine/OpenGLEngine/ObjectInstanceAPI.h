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
	static void SetTranslation(int instHandle, float in1,float in2,float in3);
	static void TestRender(int instHandle);

	static void Expose(LuaContextHandle contextHandle, string luaAPIName);

};

