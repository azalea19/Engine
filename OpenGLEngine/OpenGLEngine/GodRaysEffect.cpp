#include "GodRaysEffect.h"
#include "ShaderLibrary.h"
#include "Texture.h"

GodRaysEffect::GodRaysEffect()
{
	m_pShader = ShaderLibrary::getLib()->getShader("RayEffect");

	depthMaskTex = CreateVec3Texture();
	rayTex = CreateVec3Texture();
}

void GodRaysEffect::Apply(GLuint sceneTex, GLuint depthTex, GLuint outputTex, vec3 ssLightPos)
{
	m_depthThreshEffect.Apply(depthTex, depthMaskTex, ssLightPos.z);
	m_rayEffect.Apply(depthMaskTex, rayTex, vec2(ssLightPos.x, ssLightPos.y));
	m_additiveBlendEffect.Apply(rayTex, sceneTex, outputTex);

}
