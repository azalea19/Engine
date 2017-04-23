#include "FrameBuffer.h"
#include "Shader.h"
#include <memory>

/**
* @file MultiplicativeBlendEffect.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief 
*
*/

class MultiplicativeBlendEffect
{
public:

  MultiplicativeBlendEffect();

  void Apply(GLuint inputTex0, GLuint inputTex1, GLuint outputTex);

private:
  FrameBuffer m_fb;
  std::unique_ptr<IShader> const& m_pShader;

};
