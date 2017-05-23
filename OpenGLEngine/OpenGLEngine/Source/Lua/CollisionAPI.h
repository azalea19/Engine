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
	static bool RayToAABB(LuaRef ray, LuaRef aabb);

  void CreateCollisionTree(LuaRef objectInstanceHandles);

  bool CollidingInTree(LuaRef box);

  bool CollidingInTree(InstanceHandle objectInstance);


	/// <summary>
	/// Exposes this lua API.
	/// </summary>
	/// <param name="contextHandle">The context handle.</param>
	/// <param name="luaAPIName">Name of the lua API.</param>
	static void Expose(LuaContextHandle contextHandle, string luaAPIName);


private:

  KDTree* collisionTree;


};

#endif // CollisionAPI_h__
