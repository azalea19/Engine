/**
*/

#pragma once

#include "PrimitiveCollisions.h"
#include "Types.h"
#include "GeometricPrimitives.h"

static class IslandCollision
{
public:

	/// <summary>
	/// Checks if one AABB is colliding with another, true if colliding.
	/// </summary>
	/// <param name="a">First AABB</param>
	/// <param name="b">Second AABB</param>
	/// <returns>bool</returns>
	static bool Check(mAABB a, mAABB b);

	/// <summary>
	/// Checks if one AABB is colliding with any in a list of AABBs, true if colliding.
	/// </summary>
	/// <param name="box">First AABB</param>
	/// <param name="list">List of AABBs</param>
	/// <param name="listSize">Size of AABB list</param>

	/// <returns>bool</returns>
	static bool Check(mAABB box, std::vector<mAABB> list, int listSize);

	/// <summary>
	/// Given the current origin of a colliding AABB, returns the new origin for it
	/// that will resolve the collision with any static objects.
	/// </summary>
	/// <param name="toMoveOrigin">Origin of current bounding box to move when colliding</param>
	/// <param name="toMoveBB">Current bounding box to move when colliding</param>
	/// <param name="staticBB">Static bounding box</param>
	/// <param name="inc">Size of movement increments</param>
	/// <returns>vec3</returns>
	static vec3 Resolve(vec3 toMoveOrigin, mAABB toMoveBB, mAABB staticBB, float inc);


};

