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

  /// <summary>
  /// Initializes a new instance of the <see cref="AdditiveBlendEffect"/> class.
  /// </summary>
  AdditiveBlendEffect();

  /// <summary>
  /// Applies the additive blend effect.
  /// </summary>
  /// <param name="inputTex0">The input tex0.</param>
  /// <param name="inputTex1">The input tex1.</param>
  /// <param name="outputTex">The output tex.</param>
  void Apply(GLuint inputTex0, GLuint inputTex1, GLuint outputTex);

private:

  /// <summary>
  /// The frame buffer
  /// </summary>
  FrameBuffer m_fb;

  /// <summary>
  /// The shader
  /// </summary>
  std::unique_ptr<IShader> const& m_pShader;
};

#endif // AdditiveBlendEffect_h__
