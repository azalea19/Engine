#include "ExampleScene.h"
#include "ModelLibrary.h"
#include "Types.h"
#include "MCamera.h"
#include "InputManager.h"
//#include "RigidBody.h"
//#include "MPlayer.h"
#include "ShaderLibrary.h"
#include "Utility.h"
#include "SoundManager.h"

static float ROOM_MIN_X = -500;
static float ROOM_MIN_Y = 0;
static float ROOM_MIN_Z = -500;
static float ROOM_MAX_X = 500;
static float ROOM_MAX_Y = 500;
static float ROOM_MAX_Z = 500;


static float FIN_MIN_X = -350;
static float FIN_MIN_Z = -350;
static float FIN_MAX_X = -150;
static float FIN_MAX_Z = -150;

ExampleScene::ExampleScene()
{
	//player = new MPlayer();
	//player->SetPosition(vec3(0, 0, 0));
}

void ExampleScene::Initialise()
{
	//ModelLibrary::getLib()->addModel("example_cube", "cube.obj", true);
	//ModelLibrary::getLib()->addModel("example_rabbit", "Rabbit.obj", true);
	//
	//ShaderLibrary::getLib()->addShader("gridShade", CreateVector(string("mvp"), string("diffuse")), CreateVector(string("position"), string("uvIn")));

	//room = new RigidBody(ModelLibrary::getLib()->getInstance("example_cube"));
	//room->SetScale(vec3(ROOM_MAX_X - ROOM_MIN_X, ROOM_MAX_Y - ROOM_MIN_Y, ROOM_MAX_Z - ROOM_MIN_Z));
	//room->SetPosition(vec3(0, (ROOM_MAX_Y + ROOM_MIN_Y) / 2, 0));

	//lilRabbit = new RigidBody(ModelLibrary::getLib()->getInstance("example_rabbit"));
	//lilRabbit->SetScale(vec3(50, 50, 50));
	//lilRabbit->SetPosition(vec3(0, 25, 0));

	//finishPlatform = new RigidBody(ModelLibrary::getLib()->getInstance("example_cube"));
	//finishPlatform->SetScale(vec3(FIN_MAX_X - FIN_MIN_X, 0.1, FIN_MAX_X - FIN_MIN_X));
	//finishPlatform->SetPosition(vec3((FIN_MAX_X + FIN_MIN_X)/2, 1, (FIN_MAX_Z + FIN_MIN_Z) / 2));

}

bool ExampleScene::Finished()
{
	//vec3 position = player->GetPosition();

	//if (position.x < FIN_MIN_X || position.x > FIN_MAX_X)
	//{
	//	return false;
	//}
	//if (position.z < FIN_MIN_Z || position.z > FIN_MAX_Z)
	//{
	//	return false;
	//}
	//if (InputManager::GetInputManager()->IsKeyPressed(SDL_SCANCODE_F))
	//{
	//	return true;
	//}

	//return false;
	return false;
}

void ExampleScene::Render()
{
	//const MCamera* camera = player->GetCamera();
	//mat4 projectionMatrix = camera->getProjectionMatrix();
	//mat4 viewMatrix = camera->getViewMatrix();

	//ShaderLibrary::getLib()->bindShader("gridShade");
	//room->Render(viewMatrix, projectionMatrix);
	//ShaderLibrary::getLib()->bindDefaultShader();

	//ShaderLibrary::getLib()->bindShader("textured");
	//lilRabbit->Render(viewMatrix, projectionMatrix);
	//ShaderLibrary::getLib()->bindDefaultShader();

	//ShaderLibrary::getLib()->bindShader("textured");
	//finishPlatform->Render(viewMatrix, projectionMatrix);
	//ShaderLibrary::getLib()->bindDefaultShader();

}

void ExampleScene::UpdatePlayer()
{
	//InputManager* im = InputManager::GetInputManager();
	//MCamera* camera = player->GetCamera();

	////Rotation
	//float turnSpeed = 0.1f;
	//float originalYaw = camera->getYaw();
	//float originalPitch = camera->getPitch();
	//float deltaYaw = -im->MouseDeltaX() * turnSpeed;
	//float deltaPitch = -im->MouseDeltaY() * turnSpeed;
	//camera->SetYaw(originalYaw + deltaYaw);
	//camera->SetPitch(originalPitch + deltaPitch);

	////Translation
	//float moveSpeed = 10.0f;
	//vec3 oldPos = camera->GetPosition();
	//vec3 forward = camera->ForwardNoPitch();
	//vec3 right = camera->Right();
	//vec3 translation = vec3{ 0, 0, 0 };

	//if (im->IsKeyDown(SDL_SCANCODE_W))
	//	translation += forward;
	//if (im->IsKeyDown(SDL_SCANCODE_A))
	//	translation -= right;
	//if (im->IsKeyDown(SDL_SCANCODE_S))
	//	translation -= forward;
	//if (im->IsKeyDown(SDL_SCANCODE_D))
	//	translation += right;

	//if (translation != vec3{ 0, 0, 0 })
	//{
	//	//Normalize so you dont move faster diagonally
	//	translation = normalize(translation);

	//	translation *= moveSpeed;
	//}

	////Clamp Player to room
	//vec3 newPos = oldPos + translation;
	//newPos.x = mClamp(newPos.x, ROOM_MIN_X + 10, ROOM_MAX_X - 10);
	//newPos.y = mClamp(newPos.y, ROOM_MIN_Y + 10, ROOM_MAX_Y - 10);
	//newPos.z = mClamp(newPos.z, ROOM_MIN_Z + 10, ROOM_MAX_Z - 10);
	//camera->SetPosition(newPos);

}

void ExampleScene::Update()
{
	UpdatePlayer();
}