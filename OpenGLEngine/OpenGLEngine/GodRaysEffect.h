#ifndef GodRaysEffect_h__
#define GodRaysEffect_h__

#include "AdditiveBlendEffect.h"
#include "DepthThresholdEffect.h"
#include "RayEffect.h"
#include "FrameBuffer.h"
#include "Shader.h"
#include <memory>

/**
* @file GodRaysEffect.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief Accepts an input texture and uses a combination of effects to simulate a god rays effect.
*
*/

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

  std::unique_ptr<IShader> const& m_pShader;

	GLuint depthMaskTex;
	GLuint rayTex;
};

#endif
