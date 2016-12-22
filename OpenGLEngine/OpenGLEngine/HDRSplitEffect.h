#include "FrameBuffer.h"


class Shader;

class HDRSplitEffect
{
  FrameBuffer m_fb;
  Shader const* m_pShader;

public:
  HDRSplitEffect();
  void Apply(GLuint inputTex, GLuint outLowTex, GLuint outHightTex);
};
