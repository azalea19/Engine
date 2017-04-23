
#include "RenderManagerAPI.h"
#include "LuaObjectInstanceManager.h"
#include "GBuffer.h"
#include "EngineAPI.h"

SceneDecomposeEffect* pDecomposeEffect;
DepthThresholdEffect* pThresholdEffect;
GodRaysEffect* pRayEffect;
BloomEffect* pBloomEffect;
FXAAEffect* pFXAAEffect;
MultiplicativeBlendEffect* pBlendEffect;
DirectionalLightingEffect* pLightingEffect;
GLuint godRayMaskTexture;
GBuffer* buffers;
GLuint finalTex;
GLuint tempTex;
GLuint tempTex2;

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
	ObjectInstance * obj = LuaObjectInstanceManager::GetInstance(object);
	RenderManager::GetInstance().AddObject(obj);
}

void RenderManagerAPI::Initialise()
{

	TextureLibrary::GetInstance().InitTextureLibrary();
  FrameBuffer::Initialize();

	pDecomposeEffect = new SceneDecomposeEffect();
	pThresholdEffect = new DepthThresholdEffect();
	pRayEffect = new GodRaysEffect();
	pBloomEffect = new BloomEffect();
	pFXAAEffect = new FXAAEffect();
	pBlendEffect = new MultiplicativeBlendEffect();
	pLightingEffect = new DirectionalLightingEffect();
	
  buffers = new GBuffer();
	godRayMaskTexture = CreateVec3Texture();
	finalTex = CreateVec3Texture();
  tempTex = CreateVec3Texture();
  tempTex2 = CreateVec3Texture();

}

static void SetEffect(string const& shader)
{
  
}

void RenderManagerAPI::RenderObject(int camID, float time, int instanceHandle)
{
  MCamera *cam = InstanceManager<MCamera>().GetInstance().GetInst(camID);
  mat4 world;

  pDecomposeEffect->Bind(*buffers);

  LuaObjectInstanceManager::GetInstance(instanceHandle)->Render(mat4(), cam->getViewMatrix(), cam->getProjectionMatrix());

}

void RenderManagerAPI::BeginRender()
{
  pDecomposeEffect->Bind(*buffers);
  EngineAPI::GetEngine()->BeginRender();
}

void RenderManagerAPI::EndRender()
{
  EngineAPI::GetEngine()->EndRender();
}


void RenderManagerAPI::Present()
{
  pDecomposeEffect->Unbind();
  pLightingEffect->Apply(buffers->GetNormalBuffer(), tempTex, vec3(0.5, 0.5, 0.5), vec3(1, -1, 1));
  
  pBlendEffect->Apply(tempTex, buffers->GetColorBuffer(), tempTex2);
  
  pBloomEffect->Apply(tempTex2,finalTex, 1);

  FrameBuffer::Display(finalTex);
}

void RenderManagerAPI::RenderFromCamera(int camID, float time)
{
	    MCamera *cam = InstanceManager<MCamera>().GetInstance().GetInst(camID);
	    mat4 world;
	    RenderManager rend = RenderManager::GetInstance();


			static bool renderDepth = true;
		
			vec3 lightPos;

			lightPos.x = -cos(PI * time / 60) * 10000;
			lightPos.y = sin(PI * time / 60) * 10000;
		
			pDecomposeEffect->Bind(*buffers);
			
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
			rend.Render(world, cam->getViewMatrix(), cam->getProjectionMatrix(), time);
			
      pDecomposeEffect->Unbind();
		
			//float camDist = glm::length(cam->GetPosition() - lightPos);
		
			//vec4 temp = cam->getViewMatrix() * vec4(lightPos, 1.0);
			//vec3 vsLightPos = vec3(temp.x, temp.y, temp.z);
			//float lightDist = length(vsLightPos);
			//temp = cam->getProjectionMatrix() * vec4(vsLightPos, 1.0);
			//temp.x = temp.x / temp.w;
			//temp.y = temp.y / temp.w;
			//vec3 ssLightPos = vec3(temp.x, temp.y, lightDist);
		
			//if (vsLightPos.z > 0)
			//{
			//	pLightingEffect->Apply(buffers->GetNormalBuffer(), godRayMaskTexture, vec3(0.5, 0.5, 0.4), normalize(-lightPos));
			//	pBlendEffect->Apply(buffers->GetColorBuffer(), godRayMaskTexture, tempTex);
			//}
			//else
			//{
			//	pLightingEffect->Apply(buffers->GetNormalBuffer(), godRayMaskTexture, vec3(0.5, 0.5, 0.4), normalize(-lightPos));
			//	pBlendEffect->Apply(godRayMaskTexture, buffers->GetColorBuffer(), finalTex );
			//	pRayEffect->Apply(buffers->GetNormalBuffer(), buffers->GetLinearDepthBuffer(), tempTex, ssLightPos);
			//}
			//pBlendEffect->Apply(buffers->GetColorBuffer(), tempTex, finalTex);
		
			//pRayEffect->Apply(buffers->GetColorBuffer(), buffers->GetLinearDepthBuffer(), tempTex, ssLightPos);
			//pBloomEffect->Apply(sceneTextures[4], finalTex, 7);
			//pFXAAEffect->Apply(sceneTextures[4], finalTex, 32);
			//pFXAAEffect->Apply(godRayMaskTexture, sceneTextures[2], 8);
		
			FrameBuffer::Display(buffers->GetColorBuffer());		

}

void RenderManagerAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
  LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
  pContext->ExposeFunction(luaAPIName, "render", Render);
  pContext->ExposeFunction(luaAPIName, "renderFromCamera", RenderFromCamera);
  pContext->ExposeFunction(luaAPIName, "renderObject", RenderObject);
  pContext->ExposeFunction(luaAPIName, "addObject", AddObject);
  pContext->ExposeFunction(luaAPIName, "initialise", Initialise);
  pContext->ExposeFunction(luaAPIName, "present", Present);
  pContext->ExposeFunction(luaAPIName, "beginRender", BeginRender);
  pContext->ExposeFunction(luaAPIName, "endRender", EndRender);

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