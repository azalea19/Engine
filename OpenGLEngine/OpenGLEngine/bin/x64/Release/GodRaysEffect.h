#ifndef GodRaysEffect_h__
#define GodRaysEffect_h__

#include "AdditiveBlendEffect.h"
#include "DepthThresholdEffect.h"
#include "RayEffect.h"
#include "FrameBuffer.h"
#include "Shader.h"
#include <memory>

/**
* @file GodRaysEffect.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief Accepts an input texture and uses a combination of effects to simulate a god rays effect.
*
*/

class GodRaysEffect
{
public:

  /// <summary>
  /// Initializes a new instance of the <see cref="GodRaysEffect"/> class.
  /// </summary>
  GodRaysEffect();

  /// <summary>
  /// Applies the god rays effect.
  /// </summary>
  /// <param name="sceneTex">The scene tex.</param>
  /// <param name="depthTex">The depth tex.</param>
  /// <param name="outputTex">The output tex.</param>
  /// <param name="ssLightPos">The screen space light position.</param>
  void Apply(GLuint sceneTex, GLuint depthTex, GLuint outputTex, vec3 ssLightPos);

private:
  /// <summary>
  /// The frame buffer
  /// </summary>
  FrameBuffer m_fb;

  /// <summary>
  /// The depth threshold effect
  /// </summary>
  DepthThresholdEffect m_depthThreshEffect;

  /// <summary>
  /// The ray effect
  /// </summary>
  RayEffect m_rayEffect;

  /// <summary>
  /// The additive blend effect
  /// </summary>
  AdditiveBlendEffect m_additiveBlendEffect;

  /// <summary>
  /// The shader
  /// </summary>
  std::unique_ptr<IShader> const& m_pShader;

  /// <summary>
  /// The depth mask texture
  /// </summary>
  GLuint depthMaskTex;

  /// <summary>
  /// The ray texture
  /// </summary>
  GLuint rayTex;
};

#endif
