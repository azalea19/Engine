
#include "FrameBuffer.h"
#include "Shader.h"
#include "Types.h"
#include <memory>

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

  /// <summary>
  /// Initializes a new instance of the <see cref="DirectionalLightingEffect"/> class.
  /// </summary>
  DirectionalLightingEffect();

  /// <summary>
  /// Applies the directional lighting effect.
  /// </summary>
  /// <param name="normalTex">The normal tex.</param>
  /// <param name="outputTex">The output tex.</param>
  /// <param name="colour">The colour.</param>
  /// <param name="direction">The direction.</param>
  void Apply(GLuint normalTex, GLuint outputTex, vec3 colour, vec3 direction);

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