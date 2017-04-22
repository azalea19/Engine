#include "FrameBuffer.h"
#include "Shader.h"
#include <memory>


/**
* @file SceneDecomposeEffect.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief
*/

class SceneDecomposeEffect
{
public:

  SceneDecomposeEffect();
  void Bind(GLuint DiffuseTexture, GLuint DepthTexture, GLuint LinearDepthTexture, GLuint NormalTexture, GLuint WorldPosTexture);
  void Unbind();

private:
  FrameBuffer m_fb;
  std::unique_ptr<IShader> const& m_pShader;
};
