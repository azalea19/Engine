#include "FXAAEffect.h"
#include "ShaderLibrary.h"


FXAAEffect::FXAAEffect()
{
  m_pShader = ShaderLibrary::getLib()->getShader("FXAAEffect");
}

void FXAAEffect::Apply(GLuint inputTex, GLuint outputTex, int fxaaSpan)
{
  m_pShader->bind();
  m_fb.Bind();

  m_fb.AttachColour(0, outputTex);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  m_pShader->transmitUniform("FXAA_SPAN", fxaaSpan);
  glBindVertexArray(FrameBuffer::FSQuadVAO);
  glActiveTexture(GL_TEXTURE0 + 0);
  glBindTexture(GL_TEXTURE_2D, inputTex);
  m_pShader->transmitUniform("inputTex0", 0);
  glDrawArrays(GL_QUADS, 0, 4);
  glBindVertexArray(NULL);

  m_fb.Unbind();
}
