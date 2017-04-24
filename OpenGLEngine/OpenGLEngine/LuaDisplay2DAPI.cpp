#include "LuaDisplay2DAPI.h"


void LuaDisplay2DAPI::DrawFullScreen(string filePath)
{

	/*
	GLuint id = TextureLibrary::GetInstance().GetTexture(filePath);
	if ( id == UINT32_MAX)
	{
		id = LoadImage(filePath.c_str(), false);
		TextureLibrary::GetInstance().AddTexture(filePath, id);
	}
	FrameBuffer::Display(id);
	*/
	GLuint id = LoadImage(filePath.c_str(), false);

	FrameBuffer::Display(id);
}
void LuaDisplay2DAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "drawFullScreen", DrawFullScreen);
}
