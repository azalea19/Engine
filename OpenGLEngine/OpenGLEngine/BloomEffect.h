#ifndef BloomEffect_h__
#define BloomEffect_h__

#include "GL/glew.h"
#include "Shader.h"
#include "FrameBuffer.h"
#include "HDRSplitEffect.h"
#include "BlurEffect.h"
#include "AdditiveBlendEffect.h"


/**
* @file BloomEffect.h
* @Author Maddisen Topaz
* @date   S2, 2017
* @brief Accepts an input texture and creates a bloom effect on the texture using additive blend and blur.
*
*/

class BloomEffect
{

public:

  BloomEffect();

  /// <summary>
  /// Applies the bloom effect.
  /// </summary>
  /// <param name="inputTex">The input tex.</param>
  /// <param name="ouputTex">The ouput tex.</param>
  /// <param name="bloomRadius">The bloom radius.</param>
  void Apply(GLuint inputTex, GLuint ouputTex, int bloomRadius);

private:

  /// <summary>
  /// The frame buffer
  /// </summary>
  FrameBuffer m_fb;

  /// <summary>
  /// The split effect
  /// </summary>
  HDRSplitEffect m_splitEffect;

  /// <summary>
  /// The blur effect
  /// </summary>
  BlurEffect m_blurEffect;

  /// <summary>
  /// The blend effect
  /// </summary>
  AdditiveBlendEffect m_blendEffect;

  /// <summary>
  /// The temporary textures
  /// </summary>
  GLuint tempTex[3];
};
#endif // BloomEffect_h__