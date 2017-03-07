

#pragma once
#include "LuaContext.h"
#include "LuaManager.h"
#include "MVCView.h"
#include "RenderManager.h"

class RenderManagerAPI
{
public:
	static void Expose(LuaContextHandle contextHandle, string luaAPIName);
	static void Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time);
	static void TestRender();



};