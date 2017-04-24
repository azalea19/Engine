#ifndef SoundManager_h__
#define SoundManager_h__

#include "Types.h"
#include <unordered_map>
#include "SDL_mixer.h"
#include "Singleton.h"

/**
* @file   SoundManager.h
* @Author Maddisen Topaz
* @date   S1, 2017
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

class SoundManager : public Singleton<SoundManager>
{
public:
	
  /// <summary>
  /// Initializes the sound manager.
  /// </summary>
  static void InitSoundManager();

	
  /// <summary>
  /// Adds the sound.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <param name="filePath">The file path.</param>
  void AddSound(string name, string filePath);


  /// <summary>
  /// Plays the sound.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <param name="loopCount">The loop count.</param>
  /// <returns>ChannelHandle</returns>
  ChannelHandle PlaySound(string name, int loopCount);

	
  /// <summary>
  /// Pauses the channel.
  /// </summary>
  /// <param name="sound">The sound.</param>
  void PauseChannel(ChannelHandle sound);

	
  /// <summary>
  /// Resumes the channel.
  /// </summary>
  /// <param name="sound">The sound.</param>
  void ResumeChannel(ChannelHandle sound);

private:

  /// <summary>
  /// The sound map
  /// </summary>
  std::unordered_map<string, Mix_Chunk*> m_soundMap;

};

#endif
