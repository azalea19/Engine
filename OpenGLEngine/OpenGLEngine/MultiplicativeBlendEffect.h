#include "FrameBuffer.h"
#include "Shader.h"

class MultiplicativeBlendEffect
{
public:

  MultiplicativeBlendEffect();

  void Apply(GLuint inputTex0, GLuint inputTex1, GLuint outputTex);

private:
  FrameBuffer m_fb;
  Shader const* m_pShader;
};
