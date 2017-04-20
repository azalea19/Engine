#pragma once
#include "LuaContext.h"
#include "LuaManager.h"
#include "RenderManager.h"
#include "MathAPI.h"

#include "MCamera.h"
#include "InstanceManager.h"
#include "LuaInstanceManager.h"

class RenderManagerAPI
{
public:
	static void RenderManagerAPI::Render(LuaRef worldMatrix, LuaRef viewMatrix, LuaRef projectionMatrix, float time);
	static void RenderManagerAPI::RenderFromCamera(int camID, float time);
	static void RenderManagerAPI::AddObject(int object);


	static void Expose(LuaContextHandle contextHandle, string luaAPIName);

};