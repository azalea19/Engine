#ifndef SoundManager_h__
#define SoundManager_h__

#include "Types.h"
#include <unordered_map>
#include "SDL_mixer.h"

/**
* @file   SoundManager.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The sound manager.
*
* The sound manager uses SDL2's SDL_mixer library to handle multiple channels of sound. 
* Sounds are stored in a map and accessed using the SoundManager.
* See Lazy Foo's tutorial for setting up SDL_mixer:
* http://www.lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php
* See the following page for information on how to use the SDL_mixer API:
* https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_6.html#SEC6
*
*/


typedef int ChannelHandle;

class SoundManager
{
	std::unordered_map<string, Mix_Chunk*> soundMap;
	int numChannels;

	
	SoundManager();

public:

	
	static void initSoundManager();


	
	static SoundManager* GetSoundManager();


	
	void AddSound(string name, string filePath);



	ChannelHandle PlaySound(string name, int loopCount);

	

	void PauseChannel(ChannelHandle sound);

	

	void ResumeChannel(ChannelHandle sound);

};

#endif
