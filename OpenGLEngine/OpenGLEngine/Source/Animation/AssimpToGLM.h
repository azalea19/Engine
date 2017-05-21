#ifndef AssimpToGLM_h__
#define AssimpToGLM_h__

#include "Types.h"
#include "assimp/types.h"


mat4 ASToGLM(const aiMatrix4x4& value);

mat3 ASToGLM(const aiMatrix3x3& value);

vec2 ASToGLM(const aiVector2D& value);

vec3 ASToGLM(const aiVector3D& value);

vec4 ASToGLM(const aiColor4D& value);

quat ASToGLM(const aiQuaternion& value);

#endif