#ifndef PrintAPI_h__
#define PrintAPI_h__

#include "LuaContext.h"

class PrintAPI
{
public:
  static void Expose(LuaContextHandle contextHandle, string luaAPIName);
};
#endif // PrintAPI_h__