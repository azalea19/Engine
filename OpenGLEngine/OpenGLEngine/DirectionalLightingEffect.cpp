#include "DirectionalLightingEffect.h"
#include "ShaderLibrary.h"


DirectionalLightingEffect::DirectionalLightingEffect()
{
  m_pShader = ShaderLibrary::GetInstance().GetShader("DirectionalLightingEffect");
}

void DirectionalLightingEffect::Apply(GLuint normalTex, GLuint outputTex, vec3 colour, vec3 direction)
{
  m_fb.Bind();

  m_fb.AttachColour(0, outputTex);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  m_pShader->Bind();
  m_pShader->TransmitUniform("LIGHT_COLOUR", colour);
  m_pShader->TransmitUniform("LIGHT_DIRECTION", direction);
  glBindVertexArray(FrameBuffer::FSQuadVAO);
  glActiveTexture(GL_TEXTURE0 + 0);
  glBindTexture(GL_TEXTURE_2D, normalTex);
  m_pShader->TransmitUniform("inputTex0", 0);
  glDrawArrays(GL_QUADS, 0, 4);
  glBindVertexArray(NULL);

  m_fb.Unbind();
}
