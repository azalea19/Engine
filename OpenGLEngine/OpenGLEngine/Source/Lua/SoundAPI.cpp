#include "SoundAPI.h"
#include "SoundManager.h"


void SoundAPI::AddSound(string const& name, string filePath)
{
  SoundManager::GetInstance().AddSound(name, filePath);
}

ChannelHandle SoundAPI::PlaySound(string const& name, int loopCount)
{
  return SoundManager::GetInstance().PlaySound(name, loopCount);
}

void SoundAPI::PauseChannel(ChannelHandle sound)
{
  SoundManager::GetInstance().PauseChannel(sound);
}

void SoundAPI::ResumeChannel(ChannelHandle sound)
{
  SoundManager::GetInstance().ResumeChannel(sound);
}

void SoundAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
  LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
  pContext->ExposeFunction(luaAPIName, "addSound", AddSound);
  pContext->ExposeFunction(luaAPIName, "playSound", PlaySound);
  pContext->ExposeFunction(luaAPIName, "pauseChannel", PauseChannel);
  pContext->ExposeFunction(luaAPIName, "resumeChannel", ResumeChannel);
}

