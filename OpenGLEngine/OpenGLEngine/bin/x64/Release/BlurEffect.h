#ifndef BlurEffect_h__
#define BlurEffect_h__

#include "FrameBuffer.h"
#include "Shader.h"
#include <memory>

/**
* @file BlurEffect.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief Accepts an input texture and creates a box blur effect of the specified radius.
*
*
*/

class BlurEffect
{
public:

  /// <summary>
  /// Initializes a new instance of the <see cref="BlurEffect"/> class.
  /// </summary>
  BlurEffect();

  /// <summary>
  /// Applies the blur effect.
  /// </summary>
  /// <param name="inputTex">The input tex.</param>
  /// <param name="outputTex">The output tex.</param>
  /// <param name="blurRadius">The blur radius.</param>
  void Apply(GLuint inputTex, GLuint outputTex, int blurRadius);

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

#endif // BlurEffect_h__
