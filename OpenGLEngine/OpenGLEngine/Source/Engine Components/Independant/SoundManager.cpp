#include "SoundManager.h"
#include "ISoundManager.h"


void SoundManager::InitSoundManager(ISoundManager* engineSoundManager)
{
  soundManager = std::unique_ptr<ISoundManager>(engineSoundManager);
  soundManager->InitSoundManager();
}

void SoundManager::AddSound(string name, string filepath)
{
  soundManager->AddSound(name, filepath);
}

ChannelHandle SoundManager::PlaySound(string name, int loopCount)
{
  return soundManager->PlaySound(name, loopCount);
}

void SoundManager::ResumeChannel(ChannelHandle sound)
{
  soundManager->ResumeChannel(sound);
}

void SoundManager::PauseChannel(ChannelHandle myChannel)
{
  soundManager->PauseChannel(myChannel);
}

