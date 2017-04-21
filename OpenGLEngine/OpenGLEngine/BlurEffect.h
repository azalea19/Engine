#ifndef BlurEffect_h__
#define BlurEffect_h__

#include "FrameBuffer.h"
#include "Shader.h"


/**
* @file BlurEffect.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief Accepts an input texture and creates a box blur effect of the specified radius.
*
*
*/

class BlurEffect
{
public:

  BlurEffect();

  void Apply(GLuint inputTex, GLuint outputTex, int blurRadius);

private:
  FrameBuffer m_fb;
  IShader const* m_pShader;
};

#endif // BlurEffect_h__
