#include "IslandCollision.h"
#include "CollisionAPI.h"
#include <iostream>


bool IslandCollision::Check(mAABB a, mAABB b)
{
	if (Intersects(a, b))
	{
		return true;
	}
	return false;
}

bool IslandCollision::Check(mAABB box)
{
  return CollisionAPI::AABB_CollidingInTree(box);
}

static std::vector<vec3> directions;

static bool CheckDirections(vec3 position, mAABB box, float distance, vec3 *result)
{
  // doubling the size increment once you've checked the previous one in every direction
  for (int i = 0; i < directions.size(); i++)
  {
    // get total difference to move the object and bounding box
    vec3 tryMove = directions[i] * distance;

    //Get the original position
    vec3 newPos = position;
    //Get the original box
    mAABB newBox = box;

    //Try to move and check if this move solves the collision
    newPos += tryMove;
    newBox.min += tryMove;
    newBox.max += tryMove;

    // If the object now isn't colliding with anything we have found a step size that moves us out of collision
    if (!IslandCollision::Check(newBox))
    {
      *result = newPos;
      return false;
    }
  }
  return true;
}

int SortVec3ByHeight(const void *a, const void *b)
{
  vec3& A = *(vec3*)a;
  vec3& B = *(vec3*)b;
  if (A.y < B.y)
    return -1;
  else if (B.y < A.y)
    return 1;
  else
    return 0;
}

vec3 IslandCollision::Resolve(vec3 position, mAABB box)
{
  float accuracy = 0.001f;
  vec3 result;

  // If there is no collision to begin with
  if (!Check(box))
    return position;

  // Set static var directions if they have not been set up.
  // These are all the directions in which to check for an "escape route" from the collision.
  if (directions.empty())
  {
    int directionRes = 1;

    //Top and Bottom
    for (int x = -directionRes; x <= directionRes; x++)
    {
      for (int z = -directionRes; z <= directionRes; z++)
      {
        directions.push_back(normalize(vec3(x, directionRes, z)));
        directions.push_back(normalize(vec3(x, -directionRes, z)));
      }
    }

    //Left and Right
    for (int y = -directionRes + 1; y <= directionRes - 1; y++)
    {
      for (int z = -directionRes; z <= directionRes; z++)
      {
        directions.push_back(normalize(vec3(-directionRes, y, z)));
        directions.push_back(normalize(vec3(directionRes, y, z)));
      }
    }

    //Back and Front
    for (int x = -directionRes + 1; x <= directionRes - 1; x++)
    {
      for (int y = -directionRes + 1; y <= directionRes - 1; y++)
      {
        directions.push_back(normalize(vec3(x, y, -directionRes)));
        directions.push_back(normalize(vec3(x, y, directionRes)));
      }
    }

    qsort(directions.data(), directions.size(), sizeof(vec3), SortVec3ByHeight);
  }

  //Find initial Range
  float minRange = 0;
  float maxRange = accuracy * 1;
  while (true)
  {
    if (!CheckDirections(position, box, maxRange, &result))
      break;
    minRange = maxRange;
    maxRange *= 2;
  }

  while (true)
  {
    //Try half way between max and min
    float mid = (maxRange + minRange) / 2;

    //If colliding
    if (CheckDirections(position, box, mid, &result))
    {
      //We must still be colliding move the min range to mid value
      minRange = mid;
    }
    else
    {
      if ((maxRange - minRange) / 2 < accuracy)
        //Found the optimum position for the object
        break;

      //Otherwise our max range is too far out move it in
      maxRange = mid;
    }
  }

  return result;
}