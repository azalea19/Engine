#ifndef LuaDisplay2DAPI_h__
#define LuaDisplay2DAPI_h__


#include "Types.h"

#include "FrameBuffer.h"

#include "LuaContext.h"
#include "LuaManager.h"
#include <GL/glew.h>
#include "MathAPI.h"

#include "TextureLibrary.h"
#include "Texture.h"
#include "Interface2D.h"




class LuaDisplay2DAPI
{
public:
	static void LuaDisplay2DAPI::DrawFullScreen(string filePath);
	static void LuaDisplay2DAPI::DrawTextLua(int size, string const& filePath, string const& text, LuaRef pos, LuaRef color, int centered, int screenWidth,int screenHeight);
	static void LuaDisplay2DAPI::Expose(LuaContextHandle contextHandle, string luaAPIName);

};

#endif // LuaDisplay2DAPI_h__
