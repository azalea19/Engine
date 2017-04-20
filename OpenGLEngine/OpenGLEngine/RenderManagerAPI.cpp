
#include "RenderManagerAPI.h"

/// todo fix broken
void RenderManagerAPI::Render(LuaRef worldMatrix,LuaRef viewMatrix, LuaRef projectionMatrix, float time)
{
	mat4 world = FromLuaTable<mat4>(worldMatrix);
	mat4 view = FromLuaTable<mat4>(viewMatrix);
	mat4 proj = FromLuaTable<mat4>(projectionMatrix);

	RenderManager::GetInstance().Render(world,view,proj, time);
}

void RenderManagerAPI::AddObject(int object)
{
	ObjectInstance * obj = LuaInstanceManager::GetInstance(object);
	RenderManager::GetInstance().AddObject(obj);


}

void RenderManagerAPI::RenderFromCamera(int camID, float time)
{
	MCamera *cam = InstanceManager<MCamera>().GetInstance().GetInst(camID);
	mat4 world;
	RenderManager rend = RenderManager::GetInstance();
	rend.Render(world, cam->getViewMatrix(), cam->getProjectionMatrix(), time);
}

void RenderManagerAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "render", Render);
	pContext->ExposeFunction(luaAPIName, "renderFromCamera", RenderFromCamera);
	pContext->ExposeFunction(luaAPIName, "addObject", AddObject);


	//pContext->ExposeFunction(luaAPIName, "testRender", TestRender);
	//pContext->ExposeFunction(luaAPIName, "updatePlayer", UpdatePlayer);
}

//MCamera cam;
//glm::mat4 projMatrix = glm::perspective(3.1416f / 2, SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 10000.f);


/*
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
*/