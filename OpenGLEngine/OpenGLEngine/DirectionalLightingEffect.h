
#include "FrameBuffer.h"
#include "Shader.h"
#include "Types.h"


/**
* @file DirectionalLightingEffect.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief
*
*/

class DirectionalLightingEffect
{
public:

  DirectionalLightingEffect();

  void Apply(GLuint normalTex, GLuint outputTex, vec3 colour, vec3 direction);

private:
  FrameBuffer m_fb;
  Shader const* m_pShader;
};