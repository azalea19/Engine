#ifndef LuaManager_h__
#define LuaManager_h__

#include "Singleton.h"
#include "Types.h"
#include "LuaContext.h"
#include <unordered_map>
#include "LuaAPI.h"

class LuaManager : public Singleton<LuaManager>
{
public:

  LuaContext* GetContext(LuaContextHandle contextHandle);
  LuaContextHandle CreateContext(string scriptPath);
  void ExposeAPI(LuaContextHandle contextHandle, string luaAPIName, string apiName);
  static void Initialize();
  void AddAPI(string apiName, LuaAPIExposeFunc exposeFunc);

private:
  std::unordered_map<LuaContextHandle, LuaContext*> m_contexts;
  std::unordered_map<string, LuaAPIExposeFunc> m_apiExposeFunctions;
  LuaContextHandle nextHandle = 0;
  LuaContextHandle ReserveContextHandle();
};
#endif