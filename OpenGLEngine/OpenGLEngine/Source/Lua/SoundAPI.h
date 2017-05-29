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
	static void InitSoundManager();

	static void AddSound(string name, string filePath, LuaContextHandle cHandle);

	static ChannelHandle PlaySound(string name, int loopCount, LuaContextHandle cHandle);

	//static void PauseChannel(ChannelHandle sound, LuaContextHandle cHandle);
	//static void ResumeChannel(ChannelHandle sound, LuaContextHandle cHandle);

	static void Expose(LuaContextHandle contextHandle, string luaAPIName);
};

#endif
