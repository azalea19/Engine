#ifndef RayEffect_h__
#define RayEffect_h__

#include "FrameBuffer.h"
#include "Shader.h"

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
