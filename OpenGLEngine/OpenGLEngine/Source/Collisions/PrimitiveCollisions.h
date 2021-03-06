#ifndef PRIMITIVE_COLLISIONS_H__
#define PRIMITIVE_COLLISIONS_H__

#include "GeometricPrimitives.h"
#include <limits>

/**
* @file   PrimitiveCollisions.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  Collisions tests for geometric primitives.
*
* The various methods for testing collisions among geometric primitives.
*/


/// AABB collision by Nathan
bool Intersects(mAABB const& a, mAABB const& b);

//bool Intersects(mAABB const& aabb, mOBB const& obb);

//bool Intersects(mAABB const& aabb, mTriangle const& tri);

bool Intersects(mAABB const& aabb, mSphere const& sphere);

bool Intersects(mAABB const& aabb, mRay const& ray, float* rayEnterDist = nullptr, float* rayExitDist = nullptr);

//bool Intersects(mOBB const& a, mOBB const& b);

//bool Intersects(mOBB const& obb, mTriangle const& tri);

bool Intersects(mOBB const& obb, mSphere const& sphere);

bool Intersects(mOBB const& obb, mRay const& ray);

//bool Intersects(mTriangle const& a, mTriangle const& b);

bool Intersects(mTriangle const& tri, mSphere const& sphere);

bool Intersects(mSphere const& a, mSphere const& b);

bool Intersects(mSphere const& sphere, mRay const& ray);

bool Intersects(ConvexHull const& a, ConvexHull const& b);

#endif