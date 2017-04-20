#include "FrameBuffer.h"


class Shader;


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
  FrameBuffer m_fb;
  Shader const* m_pShader;

public:
  HDRSplitEffect();
  void Apply(GLuint inputTex, GLuint outLowTex, GLuint outHightTex);
};
