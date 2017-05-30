#include "CollisionAPI.h"
#include "ObjectInstance.h"
#include "LuaObjectInstanceManager.h"
#include "KDTree.h"

static KDTree* collisionTree = nullptr;

float CollisionAPI::RayOnObject(LuaRef ray, InstanceHandle instanceHandle)
{
  ObjectInstance* object = LuaObjectInstanceManager::GetInstance(instanceHandle);
	mRay myRay = FromLuaTable<mRay>(ray);
  mRay transformedRay = myRay;
  transformedRay.direction = normalize(myRay.direction);
  transformedRay = inverse(object->GetTransform()) * transformedRay;
  mAABB myAABB = object->GetRenderableObject()->GetBoundingBox();
  float distance;
  if (!Intersects(myAABB, transformedRay, &distance))
    return -1;

  vec3 rayEnd = transformedRay.position + transformedRay.direction * distance;

  rayEnd = vec3(object->GetTransform() * vec4(rayEnd, 1));

  return length(rayEnd - myRay.position);
}


void CollisionAPI::CreateCollisionTree(LuaRef objectInstanceHandles, int numberOfHandles)
{
  std::vector<ObjectInstance*> objects;

  ObjectInstance* newObject;
  
  for (int i = 0; i < numberOfHandles; i++)
  {
    newObject = LuaObjectInstanceManager::GetInstance(objectInstanceHandles[i + 1]);
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
	pContext->ExposeFunction(luaAPIName, "rayOnObject", RayOnObject);
  pContext->ExposeFunction(luaAPIName, "createCollisionTree", CreateCollisionTree);
  pContext->ExposeFunction(luaAPIName, "box_collidingInTree", Box_CollidingInTree);
  pContext->ExposeFunction(luaAPIName, "objectInstance_collidingInTree", ObjectInstance_CollidingInTree);
  pContext->ExposeFunction(luaAPIName, "objectCollidesWithObject", ObjectCollidesWithObject);
}