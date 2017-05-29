#include "SoundAPI.h"

void SoundAPI::InitSoundManager() 
{

}

void SoundAPI::AddSound(string name, string filePath, LuaContextHandle cHandle)
{

}

ChannelHandle SoundAPI::PlaySound(string name, int loopCount, LuaContextHandle cHandle) 
{

}

//void SoundAPI::PauseChannel(ChannelHandle sound, LuaContextHandle cHandle);
//void SoundAPI::ResumeChannel(ChannelHandle sound, LuaContextHandle cHandle);

void SoundAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "initSoundManager", InitSoundManager);
	pContext->ExposeFunction(luaAPIName, "addSound", AddSound);
	pContext->ExposeFunction(luaAPIName, "playSound", PlaySound);
}