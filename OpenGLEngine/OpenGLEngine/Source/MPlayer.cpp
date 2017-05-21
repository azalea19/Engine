#include "MPlayer.h"
#include "MCamera.h"

MPlayer::MPlayer()
{
	camera = new MCamera();
}

MCamera* MPlayer::GetCamera() const
{
	return camera;
}

vec3 MPlayer::GetPosition() const
{
	return camera->GetPosition() - vec3{ 0, height, 0 };
}

void MPlayer::SetPosition(vec3 const& position)
{
	camera->SetPosition(position + vec3{ 0, height, 0 });
}

void MPlayer::SetHeight(float Height)
{

	vec3 pos = GetPosition();

	height = Height;
	camera->SetPosition(pos + vec3(0, height, 0));
}

mRay MPlayer::GetPickingRay() const
{
	return mRay{ camera->GetPosition(),camera->Forward() };
}

float MPlayer::GetHeight() const
{
	return height;
}