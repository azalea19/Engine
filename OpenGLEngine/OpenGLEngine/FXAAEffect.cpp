#include "FXAAEffect.h"
#include "ShaderLibrary.h"


FXAAEffect::FXAAEffect()
{
  m_pShader = ShaderLibrary::GetInstance().GetShader("FXAAEffect");
}

void FXAAEffect::Apply(GLuint inputTex, GLuint outputTex, int fxaaSpan)
{
  m_pShader->Bind();
  m_fb.Bind();

  m_fb.AttachColour(0, outputTex);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  m_pShader->TransmitUniform("FXAA_SPAN", fxaaSpan);
  glBindVertexArray(FrameBuffer::FSQuadVAO);
  glActiveTexture(GL_TEXTURE0 + 0);
  glBindTexture(GL_TEXTURE_2D, inputTex);
  m_pShader->TransmitUniform("inputTex0", 0);
  glDrawArrays(GL_QUADS, 0, 4);
  glBindVertexArray(NULL);

  m_fb.Unbind();
}
