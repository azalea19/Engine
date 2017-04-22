#include "IslandCollision.h"
#include <iostream>


bool IslandCollision::Check(mAABB a, mAABB b)
{
	if (Intersects(a, b))
	{
		return true;
	}
	return false;
}

bool IslandCollision::Check(mAABB a, std::vector<mAABB> list, int listSize)
{

	//std::cout << "Checking collision with... MIN: " << a.min.x << "," << a.min.z << "," << a.min.z << ", MAX: " << a.max.x << "," << a.max.y << "," << a.max.z << "//  ";

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

vec3 IslandCollision::Resolve(vec3 toMoveOrigin, mAABB toMoveBB, std::vector<mAABB> list, int listSize, float incSize)
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

	bool cont;
	// Stop if there's no collision currently

//#include <iostream>
//	std::cout << "Checking collision to determine whether to resolve.\n";
	if (!Check(toMoveBB, list, listSize))
	{
		cont = false;
		return toMoveOrigin;

	}
	else
	{
		cont = true;
	}

	while (cont == true)
	{
		dist += increment;
		vec3 position = toMoveOrigin;

		for (int i = 1; i <= dirs.size(); i++)
		{
			position += (dirs[i] * increment * dist);
			toMoveBB.min += position; 
			toMoveBB.max += position;

			if (!Check(toMoveBB, list, listSize))
			{
				vec3 diff = position - toMoveOrigin;
				std::cout << "Item moved by " << diff.x << "," << diff.y << "," << diff.z << "\n";

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