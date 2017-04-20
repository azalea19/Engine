#ifndef RayEffect_h__
#define RayEffect_h__

#include "FrameBuffer.h"
#include "Shader.h"


/**
* @file RayEffect.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief Accepts an input texture and generate a ray effect from the specified light position.
*
*/

class RayEffect
{
public:

	RayEffect();

	void Apply(GLuint inputTex, GLuint outputTex, vec2 ssLightPos);

private:
	FrameBuffer m_fb;
	Shader const* m_pShader;
};


#endif // RayEffect_h__
