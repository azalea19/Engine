#include "FrameBuffer.h"
#include "Shader.h"

class SceneDecomposeEffect
{
public:

  SceneDecomposeEffect();
  void Bind(GLuint DiffuseTexture, GLuint DepthTexture, GLuint LinearDepthTexture, GLuint NormalTexture, GLuint WorldPosTexture);
  void Unbind();

private:
  FrameBuffer m_fb;
  Shader const* m_pShader;
};
