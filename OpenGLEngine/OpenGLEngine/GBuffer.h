#ifndef GBuffer_h__
#define GBuffer_h__

#include "gl/glew.h"

class GBuffer
{
public:

  GBuffer();

  GLuint GetColorBuffer() const;
  GLuint GetDepthBuffer() const;
  GLuint GetLinearDepthBuffer() const;
  GLuint GetWSPositionBuffer() const;
  GLuint GetNormalBuffer() const;

private:

  GLuint color;
  GLuint depth;
  GLuint linearDepth;
  GLuint wsPosition;
  GLuint normal;

};


#endif // GBuffer_h__
