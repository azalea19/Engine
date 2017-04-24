#include "MultiplicativeBlendEffect.h"
#include "ShaderLibrary.h"


MultiplicativeBlendEffect::MultiplicativeBlendEffect()
  : m_pShader(ShaderLibrary::GetInstance().GetShader("MultiplicativeBlendEffect"))
{
  
}

void MultiplicativeBlendEffect::Apply(GLuint inputTex0, GLuint inputTex1, GLuint outputTex)
{
  m_fb.Bind();

  m_fb.AttachColour(0, outputTex);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  m_pShader->Bind();
  glBindVertexArray(FrameBuffer::FSQuadVAO);

  glActiveTexture(GL_TEXTURE0 + 0);
  glBindTexture(GL_TEXTURE_2D, inputTex0);
  m_pShader->TransmitUniform("inputTex0", 0);

  glActiveTexture(GL_TEXTURE0 + 1);
  glBindTexture(GL_TEXTURE_2D, inputTex1);
  m_pShader->TransmitUniform("inputTex1", 1);

  glDrawArrays(GL_QUADS, 0, 4);
  glBindVertexArray(NULL);

  m_fb.Unbind();
}
