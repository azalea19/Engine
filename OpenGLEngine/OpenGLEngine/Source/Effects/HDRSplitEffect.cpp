#include "HDRSplitEffect.h"
#include "Shader.h"
#include "ShaderLibrary.h"

HDRSplitEffect::HDRSplitEffect()
  : m_pShader(ShaderLibrary::GetInstance().GetShader("HDRSplitEffect"))
{

}

void HDRSplitEffect::Apply(GLuint inputTex, GLuint outLowTex, GLuint outHighTex)
{
  m_fb.Bind();

  m_fb.AttachColour(0, outLowTex);
  m_fb.AttachColour(1, outHighTex);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  m_pShader->Bind();
  glBindVertexArray(FrameBuffer::FSQuadVAO);
  glActiveTexture(GL_TEXTURE0 + 0);
  glBindTexture(GL_TEXTURE_2D, inputTex);
  m_pShader->TransmitUniform("inputTex0", 0);
  glDrawArrays(GL_QUADS, 0, 4);
  glBindVertexArray(NULL);

  m_fb.Unbind();
}
