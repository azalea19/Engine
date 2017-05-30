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

  /// <summary>
  /// Initializes a new instance of the <see cref="MultiplicativeBlendEffect"/> class.
  /// </summary>
  MultiplicativeBlendEffect();

  /// <summary>
  /// Applies the blend effect.
  /// </summary>
  /// <param name="inputTex0">The input tex0.</param>
  /// <param name="inputTex1">The input tex1.</param>
  /// <param name="outputTex">The output tex.</param>
  void Apply(GLuint inputTex0, GLuint inputTex1, GLuint inverseDepthBuffer, GLuint outputTex);

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
