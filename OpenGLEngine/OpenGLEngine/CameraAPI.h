#ifndef CameraAPI_h__
#define CameraAPI_h__

#include "types.h"
#include "LuaContext.h"

class CameraAPI
{
public:

  static void Expose(LuaContextHandle contextHandle, string luaAPIName);
  {
    LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
    pContext->ExposeFunction(luaAPIName, "render", Render);
    pContext->ExposeFunction(luaAPIName, "testRender", TestRender);
    //pContext->ExposeFunction(luaAPIName, "updatePlayer", UpdatePlayer);
  }

};


#endif // CameraAPI_h__
