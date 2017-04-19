#ifndef MathAPI_h__
#define MathAPI_h__

#include "LuaContext.h"
#include "Types.h"

class MathAPI
{
public:

  static void Expose(LuaContextHandle contextHandle, string luaAPIName);
};



#endif // MathAPI_h__
