#include "SceneDecomposeEffect.h"
#include "ShaderLibrary.h"


SceneDecomposeEffect::SceneDecomposeEffect()
{
  m_pShader = ShaderLibrary::getLib()->getShader("SceneDecomposeEffect");
}

void SceneDecomposeEffect::Bind(GLuint DiffuseTexture, GLuint DepthTexture, GLuint LinearDepthTexture, GLuint NormalTexture, GLuint WorldPosTexture)
{
  m_fb.Bind();
  ShaderLibrary::getLib()->bindShader(m_pShader->getName());
  m_fb.AttachColour(0, DiffuseTexture);
  m_fb.AttachColour(1, NormalTexture);
  m_fb.AttachColour(2, WorldPosTexture);
  m_fb.AttachColour(3, LinearDepthTexture);
  m_fb.AttachDepth(DepthTexture);
}

void SceneDecomposeEffect::Unbind()
{
  m_fb.Unbind();
}
