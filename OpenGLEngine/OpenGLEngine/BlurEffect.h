#ifndef BlurEffect_h__
#define BlurEffect_h__

#include "FrameBuffer.h"
#include "Shader.h"
#include <memory>

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
  std::unique_ptr<IShader> const& m_pShader;
};

#endif // BlurEffect_h__
