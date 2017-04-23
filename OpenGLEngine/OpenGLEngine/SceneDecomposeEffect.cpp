#include "SceneDecomposeEffect.h"
#include "ShaderLibrary.h"
#include "GBuffer.h"

SceneDecomposeEffect::SceneDecomposeEffect()
{

}

void SceneDecomposeEffect::Bind(GBuffer const& buffers)
{
  m_fb.Bind();
  ShaderLibrary::GetInstance().BindShader("SceneDecomposeEffect");
  m_fb.AttachColour(0, buffers.GetColorBuffer());
  m_fb.AttachColour(1, buffers.GetNormalBuffer());
  m_fb.AttachColour(2, buffers.GetWSPositionBuffer());
  m_fb.AttachColour(3, buffers.GetLinearDepthBuffer());
  m_fb.AttachDepth(buffers.GetDepthBuffer());
}

void SceneDecomposeEffect::Unbind()
{
  m_fb.Unbind();
}
