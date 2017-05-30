#include "AffineTransformable.h"
#include <glm/gtx/matrix_decompose.hpp>
#include "MMath.h"

AffineTransformable::AffineTransformable(vec3 const& translation, float yaw, float pitch, float roll, vec3 const& scale)
{
  SetTranslation(translation);
  SetOrientation(yaw, pitch, roll);
  SetScale(scale);
}

AffineTransformable::AffineTransformable()
  : m_translation(0)
  , m_scale(1, 1, 1)
{
  SetOrientation(0, 0, 0);
}

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

mat4 const& AffineTransformable::GetOrientation() const
{
  return mat4(quat(vec3(m_pitch, m_yaw, m_roll)));
}

void AffineTransformable::SetOrientation(float yaw, float pitch, float roll)
{
  SetYaw(yaw);
  SetPitch(pitch);
  SetRoll(roll);
}

float AffineTransformable::GetYaw() const
{
  return RadToDeg(m_yaw);
}

void AffineTransformable::SetYaw(float yaw)
{
  m_yaw = DegToRad(yaw);
}

float AffineTransformable::GetPitch() const
{
  return RadToDeg(m_pitch);
}

void AffineTransformable::SetPitch(float pitch)
{
  m_pitch = DegToRad(pitch);
}

float AffineTransformable::GetRoll() const
{
  return RadToDeg(m_roll);
}

void AffineTransformable::SetRoll(float roll)
{
  m_roll = DegToRad(roll);
}

vec3 const& AffineTransformable::GetScale() const
{
  return m_scale;
}


vec3 AffineTransformable::Forward() const
{
	vec4 vsForward(0, 0, -1, 0);
	vec4 wsForward = GetTransform() * vsForward;
	return normalize(vec3(wsForward.x, wsForward.y, wsForward.z));
}

vec3 AffineTransformable::Backward() const
{
	return -Forward();
}

void AffineTransformable::LookAt(vec3 targetTranslation, vec3 upVector)
{
	if (GetTranslation() == targetTranslation)
	{
		return;
	}
	targetTranslation.y = GetTranslation().y;
	SetTransform(glm::inverse(glm::lookAt(GetTranslation(), targetTranslation, upVector)) * glm::scale(m_scale));
}

void AffineTransformable::LookAt(vec3 targetTranslation)
{
	
	LookAt(targetTranslation, vec3(0, 1, 0));
}



vec3 AffineTransformable::Down() const
{
	vec4 vsDown(0, -1, 0, 0);
	vec4 wsDown = GetTransform() * vsDown;

	return normalize(vec3(wsDown.x, wsDown.y, wsDown.z));
}

vec3 AffineTransformable::Up() const
{
	return -Down();
}

vec3 AffineTransformable::Left() const
{
	vec4 vsLeft(-1, 0, 0, 0);
	vec4 wsLeft = GetTransform() * vsLeft;
	return normalize(vec3(wsLeft.x, wsLeft.y, wsLeft.z));
}

vec3 AffineTransformable::Right() const
{
	return -Left();
}



void AffineTransformable::SetScale(vec3 const& scale)
{
  m_scale = scale;
}

mat4 AffineTransformable::GetTransform() const
{
  mat4 translationMatrix = translate(m_translation);
  mat4 rotationMatrix = GetOrientation();
  mat4 scaleMatrix = scale(m_scale);
  return translationMatrix * scaleMatrix * rotationMatrix;
}

void AffineTransformable::SetTransform(mat4 const& transform)
{
  quat temp;
  vec3 skew;
  vec3 tempScale;
  vec4 perspective;
  glm::decompose(transform, m_scale, temp, m_translation, skew, perspective);

  vec3 eulers = RadToDeg(eulerAngles(temp));
  SetOrientation(-eulers.y, eulers.x, eulers.z);
}

void AffineTransformable::SetTransform(vec3 const& translation, float yaw, float pitch, float roll, vec3 const& scale)
{
  SetTranslation(translation);
  SetOrientation(yaw, pitch, roll);
  SetScale(scale);
}
