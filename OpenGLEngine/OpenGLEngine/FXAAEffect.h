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

  FXAAEffect();

  void Apply(GLuint inputTex, GLuint outputTex, int fxaaSpan);

private:

  FrameBuffer m_fb;

  std::unique_ptr<IShader> const& m_pShader;
};

