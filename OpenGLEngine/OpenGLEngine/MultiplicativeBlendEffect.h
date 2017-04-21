#include "FrameBuffer.h"
#include "Shader.h"


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
  IShader const* m_pShader;
};
