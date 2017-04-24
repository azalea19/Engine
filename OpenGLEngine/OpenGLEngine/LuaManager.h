#ifndef LuaManager_h__
#define LuaManager_h__

#include "Singleton.h"
#include "Types.h"
#include "LuaContext.h"
#include <unordered_map>
#include "LuaAPI.h"


/**
* @file LuaManager.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief 
*
*/

class LuaManager : public Singleton<LuaManager>
{
public:

	/// <summary>
	/// Gets the context.
	/// </summary>
	/// <param name="contextHandle">The context handle.</param>
	/// <returns></returns>
	LuaContext* GetContext(LuaContextHandle contextHandle);
	/// <summary>
	/// Creates the context.
	/// </summary>
	/// <param name="scriptPath">The script path.</param>
	/// <returns></returns>
	LuaContextHandle CreateContext(string scriptPath);
	/// <summary>
	/// Exposes the API.
	/// </summary>
	/// <param name="contextHandle">The context handle.</param>
	/// <param name="luaAPIName">Name of the lua API.</param>
	/// <param name="apiName">Name of the API.</param>
	void ExposeAPI(LuaContextHandle contextHandle, string luaAPIName, string apiName);
	/// <summary>
	/// Initializes this instance.
	/// </summary>
	static void Initialize();
  /// <summary>
  /// Adds the API.
  /// </summary>
  /// <param name="apiName">Name of the API.</param>
  /// <param name="exposeFunc">The expose function.</param>
  void AddAPI(string apiName, LuaAPIExposeFunc exposeFunc);

private:
	/// <summary>
	/// The lua contexts
	/// </summary>
	std::unordered_map<LuaContextHandle, LuaContext*> m_contexts;
	/// <summary>
	/// The m API expose functions
	/// </summary>
	std::unordered_map<string, LuaAPIExposeFunc> m_apiExposeFunctions;
	/// <summary>
	/// The next handle
	/// </summary>
	LuaContextHandle nextHandle = 0;
	/// <summary>
	/// Reserves the context handle.
	/// </summary>
	/// <returns></returns>
	LuaContextHandle ReserveContextHandle();
};
#endif