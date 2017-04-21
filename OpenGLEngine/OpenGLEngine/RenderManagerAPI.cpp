
#include "RenderManagerAPI.h"



SceneDecomposeEffect* pDecomposeEffect;
DepthThresholdEffect* pThresholdEffect;
GodRaysEffect* pRayEffect;
BloomEffect* pBloomEffect;
FXAAEffect* pFXAAEffect;
MultiplicativeBlendEffect* pBlendEffect;
DirectionalLightingEffect* pLightingEffect;
GLuint godRayMaskTexture;
GLuint sceneTextures[5];
GLuint finalTex;

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

void RenderManagerAPI::Initialise()
{

	TextureLibrary::GetInstance().InitTextureLibrary();
	//SoundManager::GetInstance().InitSoundManager();
	FrameBuffer::Initialize();


	//ShaderLibrary::GetInstance().BindDefaultShader();


	pDecomposeEffect = new SceneDecomposeEffect();
	pThresholdEffect = new DepthThresholdEffect();
	pRayEffect = new GodRaysEffect();
	pBloomEffect = new BloomEffect();
	pFXAAEffect = new FXAAEffect();
	pBlendEffect = new MultiplicativeBlendEffect();
	pLightingEffect = new DirectionalLightingEffect();
	
	sceneTextures[0] = CreateColourFTexture();
	sceneTextures[1] = CreateDepthTexture();
	sceneTextures[2] = CreateVec3Texture();
	sceneTextures[3] = CreateVec3Texture();
	sceneTextures[4] = CreateVec3Texture();
	
	godRayMaskTexture = CreateVec3Texture();
	finalTex = CreateVec3Texture();
	
	//LuaManager::Initialize();

}

void RenderManagerAPI::RenderFromCamera(int camID, float time)
{
	MCamera *cam = InstanceManager<MCamera>().GetInstance().GetInst(camID);
	mat4 world;

	RenderManager rend = RenderManager::GetInstance();



			static bool renderDepth = true;
		
		
			
			vec3 lightPos;
			//float PI = 3.14;
			/*
			vec3 tr = pZombie->GetTranslation();
			tr.z = -50 + 1.6f * time;
			pZombie->SetTranslation(tr);
			*/
			lightPos.x = -cos(PI * time / 60) * 10000;
			lightPos.y = sin(PI * time / 60) * 10000;
		
			pDecomposeEffect->Bind(sceneTextures[0], sceneTextures[1], sceneTextures[2], sceneTextures[3], sceneTextures[4]);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
			rend.Render(world, cam->getViewMatrix(), cam->getProjectionMatrix(), time);
			pDecomposeEffect->Unbind();
		
			float camDist = glm::length(cam->GetPosition() - lightPos);
		
			//pThresholdEffect->Apply(sceneTextures[2], godRayMaskTexture, camDist);
		
			vec4 temp = cam->getViewMatrix() * vec4(lightPos, 1.0);
			vec3 vsLightPos = vec3(temp.x, temp.y, temp.z);
			float lightDist = length(vsLightPos);
			temp = cam->getProjectionMatrix() * vec4(vsLightPos, 1.0);
			temp.x = temp.x / temp.w;
			temp.y = temp.y / temp.w;
			vec3 ssLightPos = vec3(temp.x, temp.y, lightDist);
		
			if (vsLightPos.z > 0)
			{
				pLightingEffect->Apply(sceneTextures[3], godRayMaskTexture, vec3(0.5, 0.5, 0.4), normalize(-lightPos));
				pBlendEffect->Apply(sceneTextures[0], godRayMaskTexture, sceneTextures[4]);
			}
			else
			{
				pLightingEffect->Apply(sceneTextures[3], godRayMaskTexture, vec3(0.5, 0.5, 0.4), normalize(-lightPos));
				pBlendEffect->Apply(godRayMaskTexture, sceneTextures[0], sceneTextures[3]);
				pRayEffect->Apply(sceneTextures[3], sceneTextures[2], sceneTextures[4], ssLightPos);
			}
			pBlendEffect->Apply(sceneTextures[0], godRayMaskTexture, finalTex);
		
			pRayEffect->Apply(sceneTextures[0], sceneTextures[2], godRayMaskTexture, ssLightPos);
			pBloomEffect->Apply(sceneTextures[4], finalTex, 7);
			pFXAAEffect->Apply(sceneTextures[4], finalTex, 32);
			pFXAAEffect->Apply(godRayMaskTexture, sceneTextures[2], 8);
		
			if (renderDepth)
			{
				FrameBuffer::Display(finalTex);
			}
			else
			{
				FrameBuffer::Display(sceneTextures[4]);
			}
		


}

void RenderManagerAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "render", Render);
	pContext->ExposeFunction(luaAPIName, "renderFromCamera", RenderFromCamera);
	pContext->ExposeFunction(luaAPIName, "addObject", AddObject);
	pContext->ExposeFunction(luaAPIName, "initialise", Initialise);



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