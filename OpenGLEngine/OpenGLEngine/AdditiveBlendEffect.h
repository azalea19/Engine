#ifndef AdditiveBlendEffect_h__
#define AdditiveBlendEffect_h__

#include "FrameBuffer.h"
#include "Shader.h"
#include <memory>

/**
* @file AdditiveBlendEffect.h
* @Author Maddisen Topaz
* @date   S2, 2017
* @brief Allows the blending of two textures to create a high dynamic range texture.
*
*
*/

class AdditiveBlendEffect
{
public:

  AdditiveBlendEffect();

  void Apply(GLuint inputTex0, GLuint inputTex1, GLuint outputTex);

private:

  FrameBuffer m_fb;
  std::unique_ptr<IShader> const& m_pShader;
};

#endif // AdditiveBlendEffect_h__
