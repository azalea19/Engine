#pragma once

#include "FrameBuffer.h"
#include "Shader.h"
#include <memory>


/**
* @file FXAAEffect.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief Accepts an input texture and applies a fast approximate anti aliasing effect to smooth edges.
*
*
*/

class FXAAEffect
{
public:

  /// <summary>
  /// Initializes a new instance of the <see cref="FXAAEffect"/> class.
  /// </summary>
  FXAAEffect();

  /// <summary>
  /// Applies the FXAA effect.
  /// </summary>
  /// <param name="inputTex">The input tex.</param>
  /// <param name="outputTex">The output tex.</param>
  /// <param name="fxaaSpan">The fxaa span.</param>
  void Apply(GLuint inputTex, GLuint outputTex, int fxaaSpan);

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

