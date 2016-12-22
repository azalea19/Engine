#include "GL/glew.h"
#include "Shader.h"
#include "FrameBuffer.h"
#include "HDRSplitEffect.h"
#include "BlurEffect.h"
#include "AdditiveBlendEffect.h"

class BloomEffect
{
public:

  BloomEffect();
  void Apply(GLuint inputTex, GLuint ouputTex, int bloomRadius);

private:
  FrameBuffer m_fb;
  HDRSplitEffect m_splitEffect;
  BlurEffect m_blurEffect;
  AdditiveBlendEffect m_blendEffect;
  GLuint tempTex[3];
};