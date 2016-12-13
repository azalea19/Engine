#include "MCamera.h"
#include "Types.h"
#include "MMath.h"
#include "Screen.h"

MCamera::MCamera()
	: position(vec3(0,0,0))
	, yaw(0)
	, pitch(0)
{
	projectionMatrix = glm::perspective(DegToRad(90.f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_PLANE, FAR_PLANE);
	calculateCameraMatrix();
}

MCamera::MCamera(float fov, int screenwidth, int screenheight, float nearplane, float farplane)
{
	projectionMatrix = glm::perspective(DegToRad(fov), (float)screenwidth / screenheight, nearplane, farplane);
	calculateCameraMatrix();
}

void MCamera::SetClipPlanes(float near, float far)
{
  projectionMatrix = glm::perspective(DegToRad(90.f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, near, far);
}

void MCamera::calculateCameraMatrix()
{
	glm::mat4 translation = glm::translate(position);
	glm::mat4 rotateYaw = glm::rotate(yaw, vec3(0, 1, 0));
	glm::mat4 rotatePitch = glm::rotate(pitch, vec3(1, 0, 0));

	cameraMatrix = translation * rotateYaw * rotatePitch;
	viewMatrix = inverse(cameraMatrix);
}

vec3 MCamera::Forward() const
{
	vec4 vsForward(0, 0, -1, 0);
	vec4 wsForward = cameraMatrix * vsForward;
	return normalize(vec3(wsForward.x,wsForward.y,wsForward.z));
}

vec3 MCamera::Backward() const
{
	return -Forward();
}

vec3 MCamera::Down() const
{
	vec4 vsDown(0, -1, 0, 0);
	vec4 wsDown = cameraMatrix * vsDown;

	return normalize(vec3(wsDown.x, wsDown.y, wsDown.z));
}

vec3 MCamera::Up() const
{
	return -Down();
}

vec3 MCamera::Left() const
{
	vec4 vsLeft(-1, 0, 0, 0);
	vec4 wsLeft = cameraMatrix * vsLeft;
	return normalize(vec3(wsLeft.x,wsLeft.y,wsLeft.z));
}

vec3 MCamera::Right() const
{
	return -Left();
}

void MCamera::SetYaw(float deg)
{
	yaw = DegToRad(deg);
	calculateCameraMatrix();
}

void MCamera::SetPitch(float deg)
{
	deg = mMin(90, mMax(-90, deg));
	pitch = DegToRad(deg);
	calculateCameraMatrix();
}

void MCamera::SetPosition(vec3 pos)
{
	position = pos;
	calculateCameraMatrix();
}

float MCamera::getYaw() const
{
	return RadToDeg(yaw);
}

float MCamera::getPitch() const
{
	return RadToDeg(pitch);
}

vec3 MCamera::GetPosition() const
{
	return position;
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
	return viewMatrix;
}
