#pragma once
#include "Types.h"

#include "FrameBuffer.h"

#include "LuaContext.h"
#include "LuaManager.h"
#include <GL/glew.h>
#include "MathAPI.h"

#include "TextureLibrary.h"
#include "Texture.h"
#include "Interface2D.h"

#include "LuaBridge.h"



class LuaDisplay2DAPI
{
public:
	static void LuaDisplay2DAPI::DrawFullScreen(string filePath);
	static void LuaDisplay2DAPI::DrawTextLua(int size, string const& filePath, string const& text, int xpos, int ypos, LuaRef color);
	static void LuaDisplay2DAPI::Expose(LuaContextHandle contextHandle, string luaAPIName);

};

