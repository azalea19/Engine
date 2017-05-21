#ifndef DepthThresholdEffect_h__
#define DepthThresholdEffect_h__

#include "FrameBuffer.h"
#include "Shader.h"
#include <memory>

/**
* @file DepthThresholdEffect.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief
*
*/

class DepthThresholdEffect
{
public:

  /// <summary>
  /// Initializes a new instance of the <see cref="DepthThresholdEffect"/> class.
  /// </summary>
  DepthThresholdEffect();

  /// <summary>
  /// Applies the depth threshold effect.
  /// </summary>
  /// <param name="inputTex">The input tex.</param>
  /// <param name="outputTex">The output tex.</param>
  /// <param name="threshold">The threshold.</param>
  void Apply(GLuint inputTex, GLuint outputTex, float threshold);

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

#endif // DepthThresholdEffect_h__
