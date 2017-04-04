#ifndef EngineAPI_h__
#define EngineAPI_h__

#include "LuaContext.h"
#include "LuaManager.h"
#include "IEngine.h"

class EngineAPI
{

public:

  static IEngine* s_engine;

  static void Expose(LuaContextHandle contextHandle, string luaAPIName);

private:
 

};


#endif // EngineAPI_h__
