#pragma once
#include "FrameBuffer.h"

#include "LuaContext.h"
#include "LuaManager.h"
#include "TextureLibrary.h"
#include "Texture.h"


class LuaDisplay2DAPI
{
public:
	static void LuaDisplay2DAPI::DrawFullScreen(string filePath);
	static void LuaDisplay2DAPI::Expose(LuaContextHandle contextHandle, string luaAPIName);

};

