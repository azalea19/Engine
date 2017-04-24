#include "FrameBuffer.h"
#include <memory>

class IShader;


/**
* @file HDRSplit.h
* @Author Maddisen Topaz
* @date   S2, 2017
* @brief Accepts an input texture and splits the texture into two textures, 
* the original texture without the overspill and another texture that contains the HDR part of the original texture.
*
*/

class HDRSplitEffect
{

public:

  /// <summary>
  /// Initializes a new instance of the <see cref="HDRSplitEffect"/> class.
  /// </summary>
  HDRSplitEffect();

  /// <summary>
  /// Applies the HDR Split effect.
  /// </summary>
  /// <param name="inputTex">The input tex.</param>
  /// <param name="outLowTex">The out low tex.</param>
  /// <param name="outHightTex">The out hight tex.</param>
  void Apply(GLuint inputTex, GLuint outLowTex, GLuint outHightTex);

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
