#ifndef SoundManager_h__
#define SoundManager_h__

#include "Types.h"
#include <unordered_map>
#include "SDL_mixer.h"
#include "Singleton.h"
#include <memory>
#include "ISoundManager.h"

/**
* @file   SoundManager.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief  The sound manager.
*
* API independent sound manager.
*
*/


typedef int ChannelHandle;



class SoundManager : public Singleton<SoundManager>
{
public:
	
  /// <summary>
  /// Initializes the sound manager.
  /// </summary>
  void InitSoundManager(ISoundManager* engineSoundManager);

	
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

  std::unique_ptr<ISoundManager> soundManager;

};

#endif
