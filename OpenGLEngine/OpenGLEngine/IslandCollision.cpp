#include "IslandCollision.h"


bool IslandCollision::Check(mAABB a, mAABB b)
{
	if (Intersects(a, b))
	{
		return true;
	}
	return false;
}

bool IslandCollision::Check(mAABB a, mAABB * list, int listSize)
{
	for (int i = 0; i < listSize; i++)
	{
		if (Intersects(a, list[i]))
		{
			return true;
		}
	}
	return false;
}


static std::vector<vec3> dirs; // directions

vec3 IslandCollision::Resolve(vec3 toMoveOrigin, mAABB toMoveBB, mAABB staticBB, float incSize)
{
	float increment = incSize;
	float dist = increment;


	if (dirs.empty())
	{
		// y = 0 layer
		dirs.push_back(vec3(1, 0, 0)); // x 
		dirs.push_back(vec3(-1, 0, 0)); // -x
		dirs.push_back(vec3(0, 0, 1)); // z
		dirs.push_back(vec3(0, 0, -1)); //-z
		dirs.push_back(vec3(1, 0, 1)); // x z
		dirs.push_back(vec3(-1, 0, 1)); // -x z
		dirs.push_back(vec3(1, 0, -1)); // x -z
		dirs.push_back(vec3(-1, 0, -1)); // -x -z

		// y = 1 layer
		dirs.push_back(vec3(1, 1, 0)); // x 
		dirs.push_back(vec3(-1, 1, 0)); // -x
		dirs.push_back(vec3(0, 1, 1)); // z
		dirs.push_back(vec3(0, 1, -1)); //-z
		dirs.push_back(vec3(1, 1, 1)); // x z
		dirs.push_back(vec3(-1, 1, 1)); // -x z
		dirs.push_back(vec3(1, 1, -1)); // x -z
		dirs.push_back(vec3(-1, 1, -1)); // -x -z

		// y = -1 layer
		dirs.push_back(vec3(1, -1, 0)); // x 
		dirs.push_back(vec3(-1, -1, 0)); // -x
		dirs.push_back(vec3(0, -1, 1)); // z
		dirs.push_back(vec3(0, -1, -1)); //-z
		dirs.push_back(vec3(1, -1, 1)); // x z
		dirs.push_back(vec3(-1, -1, 1)); // -x z
		dirs.push_back(vec3(1, -1, -1)); // x -z
		dirs.push_back(vec3(-1, -1, -1)); // -x -z
	}


	bool cont = true;

	while (cont = true)
	{
		dist += increment;
		vec3 position = toMoveOrigin;

		for (int i = 1; i <= dirs.size(); i++)
		{
			position += (dirs[i] * increment * dist);
			toMoveBB.min += position;
			toMoveBB.max += position;

			if (!Intersects(toMoveBB, staticBB))
			{
				return (position);
			}

			position = toMoveOrigin;
		}


		if (dist > increment * 1000)
		{
			printf("Collision handling failed.\n");
			break;
		}

	}
	
}