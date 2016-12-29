#ifndef GodRaysEffect_h__
#define GodRaysEffect_h__

#include "AdditiveBlendEffect.h"
#include "DepthThresholdEffect.h"
#include "RayEffect.h"
#include "FrameBuffer.h"
#include "Shader.h"


class GodRaysEffect
{
public:

	GodRaysEffect();

	void Apply(GLuint sceneTex, GLuint depthTex, GLuint outputTex, vec3 ssLightPos);

private:
	FrameBuffer m_fb;

	DepthThresholdEffect m_depthThreshEffect;
	RayEffect m_rayEffect;
	AdditiveBlendEffect m_additiveBlendEffect;

	Shader const* m_pShader;

	GLuint depthMaskTex;
	GLuint rayTex;
};

#endif
