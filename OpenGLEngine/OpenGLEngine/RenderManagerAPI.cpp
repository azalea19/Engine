
#include "RenderManagerAPI.h"


void RenderManagerAPI::Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time)
{
	RenderManager::GetInstance().Render(worldMatrix, viewMatrix, projectionMatrix, time);
}

void RenderManagerAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "render", Render);
	pContext->ExposeFunction(luaAPIName, "testRender", TestRender);
	pContext->ExposeFunction(luaAPIName, "updatePlayer", UpdatePlayer);
}

//MCamera cam;
//glm::mat4 projMatrix = glm::perspective(3.1416f / 2, SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 10000.f);


void RenderManagerAPI::UpdatePlayer()
{
		const float TURN_SPEED = 0.3f;
		const float MOVE_SPEED = 0.5f;

		InputManager im = InputManager::GetInstance();

		//Rotation
		float originalYaw = MVCView::camera->GetYaw();
		float originalPitch = MVCView::camera->GetPitch();
		float deltaYaw = -im.MouseDeltaX() * TURN_SPEED;
		float deltaPitch = -im.MouseDeltaY() * TURN_SPEED;
		MVCView::camera->SetYaw(originalYaw + deltaYaw);
		MVCView::camera->SetPitch(originalPitch + deltaPitch);

		//Translation
		vec3 oldPos = MVCView::camera->GetPosition();
		vec3 forward = MVCView::camera->Forward();
		vec3 right = MVCView::camera->Right();
		vec3 translation = vec3{ 0, 0, 0 };

		if (im.IsKeyDown(SDL_SCANCODE_W))
			translation += forward;
		if (im.IsKeyDown(SDL_SCANCODE_A))
			translation -= right;
		if (im.IsKeyDown(SDL_SCANCODE_S))
			translation -= forward;
		if (im.IsKeyDown(SDL_SCANCODE_D))
			translation += right;

		if (translation != vec3{ 0, 0, 0 })
		{
			//Normalize so you dont move faster diagonally
			translation = normalize(translation);

			translation *= MOVE_SPEED;

			if (im.IsKeyDown(SDL_SCANCODE_LSHIFT))
				translation *= 4;

			if (im.IsKeyDown(SDL_SCANCODE_LCTRL))
				translation *= 0.25f;

			//Clamp Player to room

			vec3 newPos = oldPos;

			newPos.x += translation.x;
			newPos.y += translation.y;
			newPos.z += translation.z;
			MVCView::camera->SetPosition(newPos);
	}
}


void RenderManagerAPI::TestRender()
{
	printf("Testrender");
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);

	float time = clock() / float(CLOCKS_PER_SEC);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RenderManager::GetInstance().Render(mat4(), MVCView::camera->getViewMatrix(), MVCView::projectionMatrix, time);

	//float camDist = length(camera.GetPosition() - lightPos);


	char frameRate[32];
	sprintf_s(frameRate, "FPS: %.2f", RenderManager::GetInstance().GetFrameRate());
	//printf("%s\n", frameRate);
	DrawText(16, "Assets/Fonts/verdanab.ttf", frameRate, 0, 0, vec3(1, 1, 1));
	//glFlush();
	SDL_GL_SwapWindow(MVCView::screen);
}