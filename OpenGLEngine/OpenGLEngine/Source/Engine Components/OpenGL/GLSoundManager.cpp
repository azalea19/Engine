#include "GLSoundManager.h"

void channelFinishedCB(int channel)
{
  channels.push_back(channel);
}


void GLSoundManager::InitSoundManager()
{
  //m_numChannels = 16;

  Mix_AllocateChannels(16);

  for (int i = 0; i < 16; i++)
  {
    channels.push_back(i);
  }

  Mix_ChannelFinished(channelFinishedCB);
}

ChannelHandle GLSoundManager::PlaySound(string const& name, int loopCount) const
{
  if (channels.size() == 0)
  {
    return -1;
  }

  auto got = m_soundMap.find(name);

  if (got == m_soundMap.end())
  {
    printf("Sound with name %s not found.", name.c_str());
    return -1;
  }

  ChannelHandle channel = channels[channels.size() - 1];
  channels.pop_back();

  Mix_PlayChannel(channel, got->second, loopCount-1);

  return channel;
}

void GLSoundManager::AddSound(string const& name, string filepath)
{
  Mix_Chunk* newEffect = Mix_LoadWAV(filepath.c_str());

  if (!newEffect)
  {
    printf("Mix_LoadWAV: %s\n", Mix_GetError());
  }
  m_soundMap.emplace(name, newEffect);
}

void GLSoundManager::ResumeChannel(ChannelHandle sound) const
{
  Mix_Resume(sound);
}

void GLSoundManager::PauseChannel(ChannelHandle myChannel) const
{
  Mix_HaltChannel(myChannel);
}
