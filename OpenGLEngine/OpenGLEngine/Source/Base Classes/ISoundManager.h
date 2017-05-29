#ifndef ISoundManager_h__
#define ISoundManager_h__

#include "Types.h"

typedef int ChannelHandle;

class ISoundManager
{
public:

  virtual void InitSoundManager() = 0;

  virtual ChannelHandle PlaySound(string const& name, int loopCount) const = 0;

  virtual void AddSound(string const& name, string filepath) = 0;

  virtual void ResumeChannel(ChannelHandle sound) const = 0;

  virtual void PauseChannel(ChannelHandle myChannel) const = 0;
};

#endif // ISoundManager_h__
