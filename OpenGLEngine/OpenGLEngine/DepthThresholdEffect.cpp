#include "DepthThresholdEffect.h"
#include "ShaderLibrary.h"


DepthThresholdEffect::DepthThresholdEffect()
{
	m_pShader = ShaderLibrary::getLib()->getShader("DepthThresholdEffect");
}

void DepthThresholdEffect::Apply(GLuint inputTex, GLuint outputTex, float threshold)
{
	m_fb.Bind();

	m_fb.AttachColour(0, outputTex);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_pShader->bind();
	m_pShader->transmitUniform("threshold", threshold);
	glBindVertexArray(FrameBuffer::FSQuadVAO);
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, inputTex);
	m_pShader->transmitUniform("inputTex0", 0);
	glDrawArrays(GL_QUADS, 0, 4);
	glBindVertexArray(NULL);

	m_fb.Unbind();
}

