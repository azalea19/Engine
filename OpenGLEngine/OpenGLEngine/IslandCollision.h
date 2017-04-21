/**
*/

#pragma once

#include "PrimitiveCollisions.h"
#include "Types.h"
#include "GeometricPrimitives.h"

static class IslandCollision
{
public:
	static bool Check(mAABB a, mAABB b);
	static vec3 Resolve(vec3 toMoveOrigin, mAABB toMoveBB, mAABB staticBB, float inc);


};

