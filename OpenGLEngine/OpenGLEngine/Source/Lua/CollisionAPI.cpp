#include "CollisionAPI.h"
#include "ObjectInstance.h"
#include "LuaObjectInstanceManager.h"
#include "KDTree.h"


bool CollisionAPI::RayToAABB(LuaRef ray, LuaRef aabb)
{
	mRay myRay = FromLuaTable<mRay>(ray);
	mAABB myAABB = FromLuaTable<mAABB>(aabb);
	bool a = Intersects(myAABB, myRay);

	return a;
}

void CollisionAPI::CreateCollisionTree(LuaRef objectInstanceHandles)
{
  std::vector<InstanceHandle> handles;
  std::vector<ObjectInstance*> objects;

  int length = objectInstanceHandles["length"];

  for (int i = 0; i < length; i++)
  {
    handles.push_back(objectInstanceHandles[i]);
  }

  ObjectInstance* newObject;
  
  for (int i = 0; i < handles.size(); i++)
  {
    newObject = LuaObjectInstanceManager::GetInstance(i);
    objects.push_back(newObject);
  }

  collisionTree = new KDTree(objects, 10);

  //KD Tree created now have a bounding volume hierarchy of all objects that were passed in to the tree
}


bool CollisionAPI::CollidingInTree(LuaRef luaBox)
{
  return collisionTree->Intersects(FromLuaTable<mAABB>(luaBox));
}

bool CollisionAPI::CollidingInTree(InstanceHandle instanceHandle)
{
  mOBB box = LuaObjectInstanceManager::GetInstance(instanceHandle)->GetBoundingBox();

  return collisionTree->Intersects(box);
}


void CollisionAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "rayToAABB", RayToAABB);
}