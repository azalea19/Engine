#pragma 
#include "LuaManager.h"
#include "ObjectLoader.h"
#include "LuaInstanceManager.h"

class InstanceFileLoaderAPI
{
public:
	static void Expose(LuaContextHandle contextHandle, string luaAPIName);
	static void ReadFile(string fileName);
	static InstanceHandle ReadFromLoadedFile(int i);


};

