#ifndef RayEffect_h__
#define RayEffect_h__

#include "FrameBuffer.h"
#include "Shader.h"
#include <memory>


/**
* @file RayEffect.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief Accepts an input texture and generate a ray effect from the specified light position.
*
*/

class RayEffect
{
public:

  /// <summary>
  /// Initializes a new instance of the <see cref="RayEffect"/> class.
  /// </summary>
  RayEffect();

  /// <summary>
  /// Applies the ray effect.
  /// </summary>
  /// <param name="inputTex">The input tex.</param>
  /// <param name="outputTex">The output tex.</param>
  /// <param name="ssLightPos">The screenspace light position.</param>
  void Apply(GLuint inputTex, GLuint outputTex, vec2 ssLightPos);

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


#endif // RayEffect_h__
