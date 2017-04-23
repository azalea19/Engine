#include "GBuffer.h"
#include "Texture.h"

GBuffer::GBuffer()
{
  color = CreateColourFTexture();
  depth = CreateDepthTexture();
  linearDepth = CreateVec3Texture();
  wsPosition = CreateVec3Texture();
  normal = CreateVec3Texture();
}

GLuint GBuffer::GetColorBuffer() const
{
  return color;
}

GLuint GBuffer::GetDepthBuffer() const
{
  return depth;
}

GLuint GBuffer::GetLinearDepthBuffer() const
{
  return linearDepth;
}

GLuint GBuffer::GetWSPositionBuffer() const
{
  return wsPosition;
}

GLuint GBuffer::GetNormalBuffer() const
{
  return normal;
}
