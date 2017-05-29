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

struct mOBB
{
  vec3 corners[8];
  vec3 axes[3];

  mOBB(mAABB const& box);
};

mOBB operator*(mat4 const& lhs, mAABB const& rhs);

struct mRay
{
	vec3 position;	
	vec3 direction;	
};



mOBB operator*(mat4 const& lhs, mOBB rhs);

struct mTriangle
{
	vec3 corners[3];	
};

mTriangle operator*(mat4 const& lhs, mTriangle rhs);


struct ConvexHull
{
  std::vector<vec3> vertices;
  std::vector<vec3> axes;
  std::vector<vec3> edgeDirs;

  ConvexHull(mTriangle const& triangle);

  ConvexHull(mAABB const& box);

  ConvexHull(mOBB const& box);

};

ConvexHull operator*(mat4 const& lhs, ConvexHull rhs);


#endif // GeometricPrimitives_h__