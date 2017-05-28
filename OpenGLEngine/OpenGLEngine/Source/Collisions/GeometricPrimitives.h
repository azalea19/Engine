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


struct ConvexHull
{
  std::vector<vec3> vertices;
  std::vector<vec3> axes;
  std::vector<vec3> edgeDirs;

  ConvexHull(mTriangle const& triangle)
  {
    vertices.resize(3);

    vertices[0] = triangle.corners[0];
    vertices[1] = triangle.corners[1];
    vertices[2] = triangle.corners[2];

    const vec3 &a = triangle.corners[0];
    const vec3 &b = triangle.corners[1];
    const vec3 &c = triangle.corners[2];

    vec3 direction1 = normalize(a - b);
    vec3 direction2 = normalize(b - c);
    vec3 direction3 = normalize(c - a);
    vec3 faceNormal = glm::cross(direction1, direction2);

    axes.resize(4);

    axes[0] = glm::cross(faceNormal, direction1);
    axes[1] = glm::cross(faceNormal, direction2);
    axes[2] = glm::cross(faceNormal, direction3);
    axes[3] = faceNormal;

    edgeDirs.resize(3);
    edgeDirs[0] = direction1;
    edgeDirs[1] = direction2;
    edgeDirs[2] = direction3;
  }

  ConvexHull(mAABB const& box)
  {
    vertices.resize(8);
    axes.resize(3);
    edgeDirs.resize(3);

    vertices[0] = vec3(box.min.x, box.min.y, box.min.z);
    vertices[1] = vec3(box.min.x, box.min.y, box.max.z);
    vertices[2] = vec3(box.min.x, box.max.y, box.min.z);
    vertices[3] = vec3(box.min.x, box.max.y, box.max.z);
    vertices[4] = vec3(box.max.x, box.min.y, box.min.z);
    vertices[5] = vec3(box.max.x, box.min.y, box.max.z);
    vertices[6] = vec3(box.max.x, box.max.y, box.min.z);
    vertices[7] = vec3(box.max.x, box.max.y, box.max.z);

    axes[0] = vec3(1, 0, 0);
    axes[1] = vec3(0, 1, 0);
    axes[2] = vec3(0, 0, 1);
    edgeDirs[0] = axes[0];
    edgeDirs[1] = axes[1];
    edgeDirs[2] = axes[2];
  }

  ConvexHull(mOBB const& box)
  {
    vertices.resize(8);
    axes.resize(3);
    edgeDirs.resize(3);

    vertices[0] = box.corners[0];
    vertices[1] = box.corners[1];
    vertices[2] = box.corners[2];
    vertices[3] = box.corners[3];
    vertices[4] = box.corners[4];
    vertices[5] = box.corners[5];
    vertices[6] = box.corners[6];
    vertices[7] = box.corners[7];

    axes[0] = box.axes[0];
    axes[1] = box.axes[1];
    axes[2] = box.axes[2];
    edgeDirs[0] = axes[0];
    edgeDirs[1] = axes[1];
    edgeDirs[2] = axes[2];
  }

};


#endif // GeometricPrimitives_h__