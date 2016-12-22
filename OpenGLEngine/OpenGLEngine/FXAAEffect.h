#pragma once

#include "FrameBuffer.h"
#include "Shader.h"

class FXAAEffect
{
public:

  FXAAEffect();

  void Apply(GLuint inputTex, GLuint outputTex, int fxaaSpan);

private:
  FrameBuffer m_fb;
  Shader const* m_pShader;
};

