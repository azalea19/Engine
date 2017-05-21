#ifndef GBuffer_h__
#define GBuffer_h__

#include "gl/glew.h"

class GBuffer
{
public:

  GBuffer();

  /// <summary>
  /// Gets the color buffer.
  /// </summary>
  /// <returns></returns>
  GLuint GetColorBuffer() const;
  /// <summary>
  /// Gets the depth buffer.
  /// </summary>
  /// <returns></returns>
  GLuint GetDepthBuffer() const;
  /// <summary>
  /// Gets the linear depth buffer.
  /// </summary>
  /// <returns></returns>
  GLuint GetLinearDepthBuffer() const;
  /// <summary>
  /// Gets the ws position buffer.
  /// </summary>
  /// <returns></returns>
  GLuint GetWSPositionBuffer() const;
  /// <summary>
  /// Gets the normal buffer.
  /// </summary>
  /// <returns></returns>
  GLuint GetNormalBuffer() const;

private:

	/// <summary>
	/// The color
	/// </summary>
	GLuint color;
	/// <summary>
	/// The depth
	/// </summary>
	GLuint depth;
	/// <summary>
	/// The linear depth
	/// </summary>
	GLuint linearDepth;
	/// <summary>
	/// The ws position
	/// </summary>
	GLuint wsPosition;
	/// <summary>
	/// The normal
	/// </summary>
	GLuint normal;

};


#endif // GBuffer_h__
