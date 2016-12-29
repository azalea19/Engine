#include "AffineTransformable.h"
#include <glm/gtx/matrix_decompose.hpp>


vec3 const& AffineTransformable::GetTranslation() const
{
  return m_translation;
}

void AffineTransformable::SetTranslation(vec3 const& translation)
{
  m_translation = translation;
}

void AffineTransformable::SetTranslation(float x, float y, float z)
{
  SetTranslation(vec3{ x, y, z });
}

quat const& AffineTransformable::GetOrientation() const
{
  return m_orientation;
}

void AffineTransformable::SetOrientation(quat const& orientation)
{
  m_orientation = orientation;
}

void AffineTransformable::SetOrientation(float yaw, float pitch, float roll)
{
  m_orientation = quat(vec3(pitch, yaw, roll));
}

float AffineTransformable::GetYaw() const
{
  return yaw(m_orientation);
}

void AffineTransformable::SetYaw(float yaw)
{
  SetOrientation(GetPitch(), yaw, GetRoll());
}

float AffineTransformable::GetPitch() const
{
  return pitch(m_orientation);
}

void AffineTransformable::SetPitch(float pitch)
{
  SetOrientation(pitch, GetYaw(), GetRoll());
}

float AffineTransformable::GetRoll() const
{
  return roll(m_orientation);
}

void AffineTransformable::SetRoll(float roll)
{
  SetOrientation(GetPitch(), GetYaw(), roll);
}

vec3 const& AffineTransformable::GetScale() const
{
  return m_scale;
}

void AffineTransformable::SetScale(vec3 const& scale)
{
  m_scale = scale;
}

mat4 AffineTransformable::GetTransform() const
{
  mat4 translationMatrix = translate(m_translation);
  quat temp = m_orientation;
  mat4 rotationMatrix = mat4(quat(m_orientation));
  mat4 scaleMatrix = scale(m_scale);
  return translationMatrix * rotationMatrix * scaleMatrix;
}

void AffineTransformable::SetTransform(mat4 const& transform)
{
  vec3 skew;
  vec4 perspective;
  glm::decompose(transform, m_scale, m_orientation, m_translation, skew, perspective);
}

void AffineTransformable::SetTransform(vec3 const& translation, quat const& orientation, vec3 const& scale)
{
  m_translation = translation;
  m_orientation = orientation;
  m_scale = scale;
}
