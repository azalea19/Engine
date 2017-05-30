#include "GLRenderManager.h"
#include "RenderManagerAPI.h"
#include "LuaObjectInstanceManager.h"
#include "GBuffer.h"
#include "EngineAPI.h"
#include "MCamera.h"
#include "LuaInstanceManager.h"
#include "SceneDecomposeEffect.h"
#include "DepthThresholdEffect.h"
#include "GodRaysEffect.h"
#include "DirectionalLightingEffect.h"
#include "MultiplicativeBlendEffect.h"
#include "BloomEffect.h"
#include "FXAAEffect.h"
#include "Texture.h"
#include "TextureLibrary.h"

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

GLRenderManager::GLRenderManager()
{

}

void GLRenderManager::BeginRender() const
{
  pDecomposeEffect->Bind(*buffers, 1);
  EngineAPI::GetEngine()->BeginRender();
}

void GLRenderManager::EndRender() const
{
  EngineAPI::GetEngine()->EndRender();
}

void GLRenderManager::Present(int camID) const
{
  MCamera *cam = InstanceManager<MCamera>().GetInstance().GetInst(camID);

  if (fillmode == 0)
  {
    FrameBuffer::Display(buffers->GetColorBuffer());
  }
  else
  {
    vec3 sunPosition = vec3(1000000, 1000000, 1000000);
    vec4 projectedSun = cam->getProjectionMatrix() * cam->getViewMatrix() * vec4(sunPosition, 1);
    projectedSun.x /= projectedSun.z;
    projectedSun.y /= projectedSun.z;
    pDecomposeEffect->Unbind();
    vec3 dir = sunPosition - cam->GetPosition();

    if (glm::dot(dir, cam->Forward()) > 0)
    {
      pLightingEffect->Apply(buffers->GetNormalBuffer(), tempTex, vec3(0.5, 0.5, 0.3), normalize(-sunPosition));
      pBlendEffect->Apply(tempTex, buffers->GetColorBuffer(), buffers->GetLinearDepthBuffer(), tempTex2);
      pRayEffect->Apply(tempTex2, buffers->GetLinearDepthBuffer(), tempTex, vec3(projectedSun.x, projectedSun.y, projectedSun.z));
      pBloomEffect->Apply(tempTex, finalTex, 2);
      pFXAAEffect->Apply(finalTex, tempTex, 8);
      FrameBuffer::Display(tempTex);
    }
    else
    {
      pLightingEffect->Apply(buffers->GetNormalBuffer(), tempTex, vec3(0.5, 0.5, 0.3), normalize(-sunPosition));
      pBlendEffect->Apply(tempTex, buffers->GetColorBuffer(), buffers->GetLinearDepthBuffer(), tempTex2);
      pFXAAEffect->Apply(tempTex2,finalTex, 8);
      FrameBuffer::Display(finalTex);
    }
  }
}

void GLRenderManager::SetFillMode(int fillMode) const
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

void GLRenderManager::RenderObject(int camID, float time, int instanceHandle, int lightingApplied) const
{
  MCamera *cam = InstanceManager<MCamera>().GetInstance().GetInst(camID);
  mat4 world;

  pDecomposeEffect->Bind(*buffers, lightingApplied);

  LuaObjectInstanceManager::GetInstance(instanceHandle)->Render(mat4(), cam->getViewMatrix(), cam->getProjectionMatrix(), time);
}

void GLRenderManager::Initialise() const
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


