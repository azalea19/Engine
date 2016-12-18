#include "AssimpToGLM.h"

mat4 ASToGLM(const aiMatrix4x4& value)
{
  mat4 result;

  result[0][0] = value.a1; result[0][1] = value.a2; result[0][2] = value.a3; result[0][3] = value.a4;
  result[1][0] = value.b1; result[1][1] = value.b2; result[1][2] = value.b3; result[1][3] = value.b4;
  result[2][0] = value.c1; result[2][1] = value.c2; result[2][2] = value.c3; result[2][3] = value.c4;
  result[3][0] = value.d1; result[3][1] = value.d2; result[3][2] = value.d3; result[3][3] = value.d4;

  return glm::transpose(result);
}

mat3 ASToGLM(const aiMatrix3x3& value)
{
  glm::mat3 result;

  result[0][0] = value.a1; result[0][1] = value.a2; result[0][2] = value.a3;
  result[1][0] = value.b1; result[1][1] = value.b2; result[1][2] = value.b3;
  result[2][0] = value.c1; result[2][1] = value.c2; result[2][2] = value.c3;

  return glm::transpose(result);
}

vec2 ASToGLM(const aiVector2D& value)
{
  return vec2(value.x, value.y);
}

vec3 ASToGLM(const aiVector3D& value)
{
  return vec3(value.x, value.y, value.z);
}

quat ASToGLM(const aiQuaternion& value)
{
  return quat(value.w, value.x, value.y, value.z);
}

vec4 ASToGLM(const aiColor4D& value)
{
  return vec4(value.r, value.g, value.b, value.a);
}