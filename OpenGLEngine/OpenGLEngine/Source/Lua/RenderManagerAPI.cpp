
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
int fillmode;
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

void RenderManagerAPI::RemoveObject(int object)
{
	ObjectInstance * obj = LuaObjectInstanceManager::GetInstance(object);
	RenderManager::GetInstance().RemoveObject(obj);
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


void RenderManagerAPI::RenderObject(int camID, float time, int instanceHandle, int lightingApplied)
{
  MCamera *cam = InstanceManager<MCamera>().GetInstance().GetInst(camID);
  mat4 world;

  pDecomposeEffect->Bind(*buffers, lightingApplied);

  LuaObjectInstanceManager::GetInstance(instanceHandle)->Render(mat4(), cam->getViewMatrix(), cam->getProjectionMatrix(), time);

}

void RenderManagerAPI::BeginRender()
{
  pDecomposeEffect->Bind(*buffers, 1);
  EngineAPI::GetEngine()->BeginRender();
}

void RenderManagerAPI::EndRender()
{
  EngineAPI::GetEngine()->EndRender();
}


void RenderManagerAPI::Present(int camID)
{
  MCamera *cam = InstanceManager<MCamera>().GetInstance().GetInst(camID);

  if (fillmode == 0)
  {
    FrameBuffer::Display(buffers->GetColorBuffer());
  }
  else
  {
    vec3 sunPosition = vec3(10000,10000,10000);
    vec4 projectedSun = cam->getProjectionMatrix() * cam->getViewMatrix() * vec4(sunPosition,1);
    projectedSun.x /= projectedSun.z;
    projectedSun.y /= projectedSun.z;
    pDecomposeEffect->Unbind();
    pLightingEffect->Apply(buffers->GetNormalBuffer(), tempTex, vec3(0.5, 0.5, 0.3), normalize(-sunPosition));
    pBlendEffect->Apply(tempTex, buffers->GetColorBuffer(), tempTex2);
    pRayEffect->Apply(tempTex2, buffers->GetLinearDepthBuffer(), tempTex,vec3(projectedSun.x, projectedSun.y, projectedSun.z));
    pBloomEffect->Apply(tempTex, finalTex, 2);
	pFXAAEffect->Apply(finalTex, tempTex, 8);
    FrameBuffer::Display(tempTex);
  }
}

void RenderManagerAPI::SetFillMode(int fillMode)
{
  fillmode = fillMode;

  switch (fillMode)
  {
    case FM_Line:
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      break;
    case FM_Fill:
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      break;
  }
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
		
	pDecomposeEffect->Bind(*buffers, 1);
			
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	rend.Render(world, cam->getViewMatrix(), cam->getProjectionMatrix(), time);
			
	pDecomposeEffect->Unbind();
		
	FrameBuffer::Display(buffers->GetColorBuffer());		

}

void RenderManagerAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
  LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
  pContext->ExposeFunction(luaAPIName, "render", Render);
  pContext->ExposeFunction(luaAPIName, "renderFromCamera", RenderFromCamera);
  pContext->ExposeFunction(luaAPIName, "renderObject", RenderObject);
  pContext->ExposeFunction(luaAPIName, "removeObject", RemoveObject);
  pContext->ExposeFunction(luaAPIName, "addObject", AddObject);
  pContext->ExposeFunction(luaAPIName, "initialise", Initialise);
  pContext->ExposeFunction(luaAPIName, "present", Present);
  pContext->ExposeFunction(luaAPIName, "beginRender", BeginRender);
  pContext->ExposeFunction(luaAPIName, "endRender", EndRender);
  pContext->ExposeFunction(luaAPIName, "setFillMode", SetFillMode);
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
	DrawText(16, "../Assets/Fonts/verdanab.ttf", frameRate, 0, 0, vec3(1, 1, 1));
	//glFlush();
	SDL_GL_SwapWindow(MVCView::screen);

}
*/