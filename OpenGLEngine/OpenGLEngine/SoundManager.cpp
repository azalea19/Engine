#include "SoundManager.h"


static SoundManager* soundManager = nullptr;

static std::vector<ChannelHandle> channels;

SoundManager::SoundManager()
{

}

SoundManager* SoundManager::GetSoundManager()
{
	return soundManager;
}

void channelFinishedCB(int channel)
{
	channels.push_back(channel);
}


void SoundManager::initSoundManager()
{
	if (soundManager == nullptr)
	{
		soundManager = new SoundManager();
		soundManager->numChannels = 16;

		Mix_AllocateChannels(soundManager->numChannels);

		for (int i = 0; i < soundManager->numChannels; i++)
		{
			channels.push_back(i);
		}
	}
	
	Mix_ChannelFinished(channelFinishedCB);
}

void SoundManager::AddSound(string name, string filepath)
{
	Mix_Chunk* newEffect = Mix_LoadWAV(filepath.c_str());
	
	if (!newEffect) 
	{
		printf("Mix_LoadWAV: %s\n", Mix_GetError());
	}
	soundMap.emplace(name, newEffect);
}

ChannelHandle SoundManager::PlaySound(string name, int loopCount)
{
	if (channels.size() == 0)
	{
		return -1;
	}

	auto got = soundMap.find(name);

	if (got == soundMap.end())
	{
		printf("Sound with name %s not found.", name.c_str());
		return -1;
	}

	ChannelHandle channel = channels[channels.size() - 1];
	channels.pop_back();

	Mix_PlayChannel(channel, got->second, loopCount);

	return channel;
}

void SoundManager::ResumeChannel(ChannelHandle sound)
{
  Mix_Resume(sound);
}

void SoundManager::PauseChannel(ChannelHandle myChannel)
{
  Mix_HaltChannel(myChannel);
}

