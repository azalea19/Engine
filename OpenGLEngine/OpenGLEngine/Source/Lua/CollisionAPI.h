#ifndef CollisionAPI_h__
#define CollisionAPI_h__


#include "LuaContext.h"
#include "LuaManager.h"
#include "LuaInstanceManager.h"
#include "MathAPI.h"
#include "GeometricPrimitives.h"
#include "PrimitiveCollisions.h"

class KDTree;

/// <summary>
/// API for checking primitive collisions in Lua
/// Author Elizabeth Haynes
/// Author MTopaz - KDTree functions
/// </summary>
class CollisionAPI
{
public:	
	/// <summary>
	/// Checks collision of ray and AABB
	/// </summary>
	/// <param name="ray">The ray.</param>
	/// <param name="aabb">The AABB.</param>
	/// <returns></returns>
	static float RayOnObject(LuaRef ray, InstanceHandle object);

  static void CreateCollisionTree(LuaRef objectInstanceHandles);

  static bool Box_CollidingInTree(LuaRef box);

  static bool AABB_CollidingInTree(const mAABB box);

  static bool ObjectInstance_CollidingInTree(InstanceHandle objectInstance);

  static bool ObjectCollidesWithObject(InstanceHandle a, InstanceHandle b);


	/// <summary>
	/// Exposes this lua API.
	/// </summary>
	/// <param name="contextHandle">The context handle.</param>
	/// <param name="luaAPIName">Name of the lua API.</param>
	static void Expose(LuaContextHandle contextHandle, string luaAPIName);


private:


};

#endif // CollisionAPI_h__
