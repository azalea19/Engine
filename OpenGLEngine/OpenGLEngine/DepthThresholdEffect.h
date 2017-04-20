#ifndef DepthThresholdEffect_h__
#define DepthThresholdEffect_h__

#include "FrameBuffer.h"
#include "Shader.h"


/**
* @file DepthThresholdEffect.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief
*
*/

class DepthThresholdEffect
{
public:

	DepthThresholdEffect();

	void Apply(GLuint inputTex, GLuint outputTex, float threshold);

private:
	FrameBuffer m_fb;
	Shader const* m_pShader;
};

#endif // DepthThresholdEffect_h__
