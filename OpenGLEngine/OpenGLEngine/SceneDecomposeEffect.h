#include "FrameBuffer.h"
#include "Shader.h"
#include <memory>


/**
* @file SceneDecomposeEffect.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief
*/

class GBuffer;

class SceneDecomposeEffect
{
public:

  SceneDecomposeEffect();
  void Bind(GBuffer const& buffers);
  void Unbind();

private:
  FrameBuffer m_fb;
};
