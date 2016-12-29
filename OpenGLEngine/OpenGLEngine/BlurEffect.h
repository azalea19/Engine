#ifndef BlurEffect_h__
#define BlurEffect_h__

#include "FrameBuffer.h"
#include "Shader.h"

class BlurEffect
{
public:

  BlurEffect();

  void Apply(GLuint inputTex, GLuint outputTex, int blurRadius);

private:
  FrameBuffer m_fb;
  Shader const* m_pShader;
};

#endif // BlurEffect_h__
