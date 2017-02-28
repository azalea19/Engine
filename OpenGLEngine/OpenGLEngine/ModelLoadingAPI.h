#include "luaContext.h"

class ModelLoadingAPI
{
public:
  static void Expose(LuaContextHandle contextHandle, string luaAPIName);

  //API functions may be declared here if you intend to use them from C, otherwise they can just be in the cpp like in the printAPI
  //API functions must be static.

private:
  //Any relevant data to make this API work
  //eg if it were an ObjectInstanceAPI you would have a Map<ObjectInstanceHandle, ObjectInstance*> at the very least.
};