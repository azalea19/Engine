#include "CollisionAPI.h"
#include "ObjectInstance.h"
#include "LuaObjectInstanceManager.h"
#include "KDTree.h"

static KDTree* collisionTree = nullptr;

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
    handles.push_back(objectInstanceHandles[i + 1]);
  }

  ObjectInstance* newObject;
  
  for (int i = 0; i < handles.size(); i++)
  {
    newObject = LuaObjectInstanceManager::GetInstance(handles[i]);
    objects.push_back(newObject);
  }

  delete collisionTree;
  collisionTree = new KDTree(objects, 32);

  //KD Tree created now have a bounding volume hierarchy of all objects that were passed in to the tree
}


bool CollisionAPI::Box_CollidingInTree(LuaRef luaBox)
{
  return collisionTree->Intersects(FromLuaTable<mAABB>(luaBox));
}

bool CollisionAPI::AABB_CollidingInTree(const mAABB box)
{
  return collisionTree->Intersects(box);
}

bool CollisionAPI::ObjectInstance_CollidingInTree(InstanceHandle instanceHandle)
{
  mOBB box = LuaObjectInstanceManager::GetInstance(instanceHandle)->GetBoundingBox();

  return collisionTree->Intersects(box);
}

bool CollisionAPI::ObjectCollidesWithObject(InstanceHandle a, InstanceHandle b)
{
  ObjectInstance *A = LuaObjectInstanceManager::GetInstance(a);
  ObjectInstance *B = LuaObjectInstanceManager::GetInstance(b);
  return Intersects(A->GetBoundingBox(), B->GetBoundingBox());
}

void CollisionAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "rayToAABB", RayToAABB);
  pContext->ExposeFunction(luaAPIName, "createCollisionTree", CreateCollisionTree);
  pContext->ExposeFunction(luaAPIName, "box_collidingInTree", Box_CollidingInTree);
  pContext->ExposeFunction(luaAPIName, "objectInstance_collidingInTree", ObjectInstance_CollidingInTree);
  pContext->ExposeFunction(luaAPIName, "objectCollidesWithObject", ObjectCollidesWithObject);
}