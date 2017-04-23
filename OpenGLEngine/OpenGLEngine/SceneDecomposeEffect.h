#include "FrameBuffer.h"
#include "Shader.h"
#include <memory>


/**
* @file SceneDecomposeEffect.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief
*/

class GBuffer;

class SceneDecomposeEffect
{
public:

  /// <summary>
  /// Initializes a new instance of the <see cref="SceneDecomposeEffect"/> class.
  /// </summary>
  SceneDecomposeEffect();

  /// <summary>
  /// Binds the specified buffers.
  /// </summary>
  /// <param name="buffers">The buffers.</param>
  /// <param name="lightingApplied">The lighting applied.</param>
  void Bind(GBuffer const& buffers, int lightingApplied);

  /// <summary>
  /// Unbinds this instance.
  /// </summary>
  void Unbind();

private:

  /// <summary>
  /// The frame buffer
  /// </summary>
  FrameBuffer m_fb;
};
