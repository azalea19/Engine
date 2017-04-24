#ifndef GeometricPrimitives_h__
#define GeometricPrimitives_h__

#include "Types.h"

/**
* @file   GeometricPrimitves.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  Structs of geometric primitives.
*
* The various geometric primitives needed for collisions.
*/

struct mSphere
{
	vec3 centre;	
	float radius;	
};

struct mAABB
{
	vec3 min;		 
	vec3 max;		
};

struct mRay
{
	vec3 position;	
	vec3 direction;	
};

struct mOBB
{
	vec3 corners[8];	
	vec3 axes[3];		
};

struct mTriangle
{
	vec3 corners[3];	
};

#endif // GeometricPrimitives_h__