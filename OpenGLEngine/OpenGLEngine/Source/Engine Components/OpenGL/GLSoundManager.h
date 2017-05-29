#ifndef GLSoundManager_h__
#define GLSoundManager_h__

#include "ISoundManager.h"
#include "Types.h"
#include <unordered_map>
#include "SDL_mixer.h"
#include "Singleton.h"



/**
* @file   GLSoundManager.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief  The sound manager.
*
* The GL sound manager uses SDL2's SDL_mixer library to handle multiple channels of sound.
* Sounds are stored in a map and accessed using the SoundManager.
* See Lazy Foo's tutorial for setting up SDL_mixer:
* http://www.lazyfoo.net/tutorials/SDL/21_sound_effects_and_music/index.php
* See the following page for information on how to use the SDL_mixer API:
* https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_6.html#SEC6
*
*/




typedef int ChannelHandle;

static std::vector<ChannelHandle> channels;



class GLSoundManager : public ISoundManager
{
public:

  virtual void InitSoundManager() override;


  virtual ChannelHandle PlaySound(string const& name, int loopCount) const override;


  virtual void AddSound(string const& name, string filepath) override;


  virtual void ResumeChannel(ChannelHandle sound) const override;


  virtual void PauseChannel(ChannelHandle myChannel) const override;

private:

  std::unordered_map<string, Mix_Chunk*> m_soundMap;
};




#endif // GLSoundManager_h__
