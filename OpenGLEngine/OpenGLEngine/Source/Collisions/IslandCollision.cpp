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

int IslandCollision::CheckAndGetIndex(mAABB a, std::vector<mAABB> list, int listSize)
{
	for (int i = 0; i < listSize; i++)
	{
		if (Intersects(a, list[i]))
		{
			return i;
		}
	}
	return 0;
}


static std::vector<vec3> dirs; // directions

vec3 IslandCollision::Resolve(vec3 toMoveOrigin, mAABB toMoveBB, std::vector<mAABB> list, int listSize, float incSize)
{
	// Increment between checks - initial distance and distance increase that occurs 
	// when repeating the check in all directions when no escape is found.
	float increment = incSize;

	// The increment 
	float dist = increment;

	// Set static var dirs if they have not been set up.
	// These are all the directions in which to check for an "escape route" from the collision.
	if (dirs.empty())
	{
		// y = 0 layer
		dirs.push_back(normalize(vec3(1, 0, 0))); // x 
		dirs.push_back(normalize(vec3(-1, 0, 0))); // -x
		dirs.push_back(normalize(vec3(0, 0, 1))); // z
		dirs.push_back(normalize(vec3(0, 0, -1))); //-z
		dirs.push_back(normalize(vec3(1, 0, 1))); // x z
		dirs.push_back(normalize(vec3(-1, 0, 1))); // -x z
		dirs.push_back(normalize(vec3(1, 0, -1))); // x -z
		dirs.push_back(normalize(vec3(-1, 0, -1))); // -x -z

		// y = 1 layer
		dirs.push_back(normalize(vec3(1, 1, 0))); // x 
		dirs.push_back(normalize(vec3(-1, 1, 0))); // -x
		dirs.push_back(normalize(vec3(0, 1, 1))); // z
		dirs.push_back(normalize(vec3(0, 1, -1))); //-z
		dirs.push_back(normalize(vec3(1, 1, 1))); // x z
		dirs.push_back(normalize(vec3(-1, 1, 1))); // -x z
		dirs.push_back(normalize(vec3(1, 1, -1))); // x -z
		dirs.push_back(normalize(vec3(-1, 1, -1))); // -x -z

		// y = -1 layer
		dirs.push_back(normalize(vec3(1, -1, 0))); // x 
		dirs.push_back(normalize(vec3(-1, -1, 0))); // -x
		dirs.push_back(normalize(vec3(0, -1, 1))); // z
		dirs.push_back(normalize(vec3(0, -1, -1))); //-z
		dirs.push_back(normalize(vec3(1, -1, 1))); // x z
		dirs.push_back(normalize(vec3(-1, -1, 1))); // -x z
		dirs.push_back(normalize(vec3(1, -1, -1))); // x -z
		dirs.push_back(normalize(vec3(-1, -1, -1))); // -x -z
	}

	// If there is no collision to begin with
	if (!Check(toMoveBB, list, listSize))
	{
		// Return the same position that was passed in
		return toMoveOrigin;
	}

	while (true)
	{
		// Go through each direction and check if you can find a way out of the collision in size increments, 
		// increasing the size increment once you've checked the previous one in every direction.
		for (int i = 0; i < dirs.size(); i++)
		{
			mAABB box = toMoveBB;
			// set final position to initial position
			vec3 position = toMoveOrigin;
			// get total difference to move the object and bounding box
			vec3 diff = (dirs[i] * dist); 

			// move object by difference									  
			position += diff;
			// move bounding box by difference
			box.min += diff; 
			box.max += diff;

			// If the object now isnt colliding with anything
			if (!Check(box, list, listSize))
			{
				//std::cout << "Item moved by " << diff.x << "," << diff.y << "," << diff.z << "\n";

				// Return the final position
				return (position);
			}
		}
		dist += increment;


		if (dist > increment * 1000)
		{
			printf("Collision handling failed.\n");
			return toMoveOrigin;
		}

	}
	
}