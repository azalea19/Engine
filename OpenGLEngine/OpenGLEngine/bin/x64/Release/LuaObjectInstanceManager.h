#pragma once
#include <unordered_map>
#include "ObjectInstance.h"
#include "Singleton.h"
#include "ModelLibrary.h"
#include "LuaContext.h"
#include "LuaManager.h"
#include "ModelLibrary.h"


/**
* @file LuaInstanceManager.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief The lua instance manager keeps track of local copies of object instances that have been created by the lua.
*
*/

typedef int InstanceHandle;


class LuaObjectInstanceManager : public Singleton<LuaObjectInstanceManager>
{
//private:
	//static std::unordered_map<int,ObjectInstance*> m_instanceMap;
	//static int m_lastIndex;

public:

  /// <summary>
  /// Adds the new object instance.
  /// </summary>
  /// <param name="modelName">Name of the model.</param>
  /// <returns>InstanceHandle</returns>.

  static InstanceHandle AddNewInstance(string const& modelName);

  /// <summary>
  /// Gets the object instance.
  /// </summary>
  /// <param name="instanceHandle">The instance handle.</param>
  /// <returns></returns>
  static ObjectInstance* GetInstance(int instanceHandle);

  /// <summary>
  /// Exposes the API functions.
  /// </summary>
  /// <param name="contextHandle">The context handle.</param>
  /// <param name="luaAPIName">Name of the lua API.</param>
  static void Expose(LuaContextHandle contextHandle, string luaAPIName);

  /// <summary>
  /// Deletes a specified object instance from the map.
  /// </summary>
  /// <param name="instanceHandle">The instance handle of the instance to delete.</param>
  static void DeleteInstance(int instanceHandle);
};