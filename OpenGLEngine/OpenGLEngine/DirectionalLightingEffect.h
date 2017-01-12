
#include "FrameBuffer.h"
#include "Shader.h"
#include "Types.h"

class DirectionalLightingEffect
{
public:

  DirectionalLightingEffect();

  void Apply(GLuint normalTex, GLuint outputTex, vec3 colour, vec3 direction);

private:
  FrameBuffer m_fb;
  Shader const* m_pShader;
};