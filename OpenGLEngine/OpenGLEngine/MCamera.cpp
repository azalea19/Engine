#include "MCamera.h"
#include "Types.h"
#include "MMath.h"
#include "Screen.h"

MCamera::MCamera()
  : AffineTransformable()
{
	projectionMatrix = glm::perspective(DegToRad(90.f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_PLANE, FAR_PLANE);
}

MCamera::MCamera(float fov, int screenwidth, int screenheight, float nearplane, float farplane)
{
	projectionMatrix = glm::perspective(DegToRad(fov), (float)screenwidth / screenheight, nearplane, farplane);
}

void MCamera::SetClipPlanes(float near, float far)
{
  projectionMatrix = glm::perspective(DegToRad(90.f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, near, far);
}

vec3 MCamera::Forward() const
{
	vec4 vsForward(0, 0, -1, 0);
	vec4 wsForward = GetTransform() * vsForward;
	return normalize(vec3(wsForward.x,wsForward.y,wsForward.z));
}

vec3 MCamera::Backward() const
{
	return -Forward();
}

vec3 MCamera::Down() const
{
	vec4 vsDown(0, -1, 0, 0);
	vec4 wsDown = GetTransform() * vsDown;

	return normalize(vec3(wsDown.x, wsDown.y, wsDown.z));
}

vec3 MCamera::Up() const
{
	return -Down();
}

vec3 MCamera::Left() const
{
	vec4 vsLeft(-1, 0, 0, 0);
	vec4 wsLeft = GetTransform() * vsLeft;
	return normalize(vec3(wsLeft.x,wsLeft.y,wsLeft.z));
}

vec3 MCamera::Right() const
{
	return -Left();
}



void MCamera::SetPosition(vec3 pos)
{
  SetTranslation(pos);
}

vec3 MCamera::GetPosition() const
{
  return GetTranslation();
}

mat4 MCamera::getProjectionMatrix() const
{
	return projectionMatrix;
}

vec3 MCamera::ForwardNoPitch() const
{
	vec3 forward = Forward();
	forward.y = 0;

	return normalize(forward);
}

vec3 MCamera::BackwardNoPitch() const
{

	return -ForwardNoPitch();
}

mat4 MCamera::getViewMatrix() const
{
  return inverse(GetTransform());
}
