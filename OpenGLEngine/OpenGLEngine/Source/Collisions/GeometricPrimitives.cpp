#include "GeometricPrimitives.h"



ConvexHull::ConvexHull(mOBB const& box)
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

ConvexHull::ConvexHull(mAABB const& box)
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

ConvexHull::ConvexHull(mTriangle const& triangle)
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
  vec3 faceNormal = normalize(glm::cross(direction1, direction2));

  axes.resize(4);

  axes[0] = normalize(glm::cross(faceNormal, direction1));
  axes[1] = normalize(glm::cross(faceNormal, direction2));
  axes[2] = normalize(glm::cross(faceNormal, direction3));
  axes[3] = faceNormal;

  edgeDirs.resize(3);
  edgeDirs[0] = direction1;
  edgeDirs[1] = direction2;
  edgeDirs[2] = direction3;
}

mOBB::mOBB(mAABB const& box)
{
  corners[0] = vec3(box.min.x, box.min.y, box.min.z);
  corners[1] = vec3(box.min.x, box.min.y, box.max.z);
  corners[2] = vec3(box.min.x, box.max.y, box.min.z);
  corners[3] = vec3(box.min.x, box.max.y, box.max.z);
  corners[4] = vec3(box.max.x, box.min.y, box.min.z);
  corners[5] = vec3(box.max.x, box.min.y, box.max.z);
  corners[6] = vec3(box.max.x, box.max.y, box.min.z);
  corners[7] = vec3(box.max.x, box.max.y, box.max.z);
  axes[0] = vec3(0, 0, 1);
  axes[1] = vec3(0, 1, 0);
  axes[2] = vec3(1, 0, 0);
}

ConvexHull operator*(mat4 const& lhs, ConvexHull rhs)
{
  for (int i = 0; i < rhs.vertices.size(); i++)
    rhs.vertices[i] = vec3(lhs * vec4(rhs.vertices[i], 1));

  mat4 normalMatrix = inverseTranspose(lhs);

  for (int i = 0; i < rhs.axes.size(); i++)
    rhs.axes[i] = vec3(lhs * vec4(rhs.axes[i], 0));

  for (int i = 0; i < rhs.edgeDirs.size(); i++)
    rhs.axes[i] = vec3(lhs * vec4(rhs.axes[i], 0));

  return rhs;
}

mTriangle operator*(mat4 const& lhs, mTriangle rhs)
{
  for (int i = 0; i < 3; i++)
    rhs.corners[i] = vec3(lhs * vec4(rhs.corners[i], 1));
  return rhs;
}

mOBB operator*(mat4 const& lhs, mOBB rhs)
{
  for (int i = 0; i < 8; i++)
    rhs.corners[i] = vec3(lhs * vec4(rhs.corners[i], 1));

  mat4 normalMatrix = inverseTranspose(lhs);
  for (int i = 0; i < 3; i++)
    rhs.axes[i] = vec3(vec4(rhs.axes[i], 0));

  return rhs;
}

mOBB operator*(mat4 const& lhs, mAABB const& rhs)
{
  return lhs * mOBB(rhs);
}
