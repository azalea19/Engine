#ifndef SoundAPI_h__
#define SoundAPI_h__

#include "LuaBridge.h"

#include "LuaContext.h"
#include "LuaManager.h"
#include "Types.h"
#include "LuaObjectInstanceManager.h"
#include "MathAPI.h"
#include "SoundManager.h"


class SoundAPI
{
public:

  static void AddSound(string const& name, string filePath);

  static ChannelHandle PlaySound(string const& name, int loopCount);

  static void PauseChannel(ChannelHandle sound);

  static void ResumeChannel(ChannelHandle sound);

  static void Expose(LuaContextHandle contextHandle, string luaAPIName);
};

#endif
