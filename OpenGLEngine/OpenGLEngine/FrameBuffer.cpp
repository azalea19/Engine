#include "FrameBuffer.h"
#include <exception>
#include "Types.h"
#include "Shader.h"
#include "ShaderLibrary.h"

GLuint FrameBuffer::FSQuadVAO;

void FrameBuffer::Initialize()
{
  glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &FrameBuffer::MAX_COLOUR_ATTACHMENTS);


  static vec2 verts[4] =
  {
    vec2(-1, 1), vec2(1, 1),
    vec2(1, -1), vec2(-1, -1)
  };

  static vec2 uvs[4] =
  {
    vec2(0, 1), vec2(1, 1),
    vec2(1, 0), vec2(0, 0)
  };

  GLuint quadBuffers[2];

  glGenVertexArrays(1, &FSQuadVAO);
  glGenBuffers(2, quadBuffers);

  glBindVertexArray(FSQuadVAO);
  glBindBuffer(GL_ARRAY_BUFFER, quadBuffers[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vec2)*4, verts, GL_STATIC_DRAW);
  glEnableVertexAttribArray(AL_Vertices);
  glVertexAttribPointer(AL_Vertices, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, quadBuffers[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vec2)*4, uvs, GL_STATIC_DRAW);
  glEnableVertexAttribArray(AL_TexCoords);
  glVertexAttribPointer(AL_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindVertexArray(NULL);
}

void FrameBuffer::BindToScreen(FrameBufferBindMode bufferMode /*= FBM_ReadWrite*/)
{
  BindFrameBuffer(0, bufferMode);
}

void FrameBuffer::Display(GLuint texture)
{
  const Shader* shader = ShaderLibrary::getLib()->getShader("TextureDisplay");

  FrameBuffer::BindToScreen();
  shader->bind();
  
  glBindVertexArray(FrameBuffer::FSQuadVAO);
  glActiveTexture(GL_TEXTURE0 + 0);
  glBindTexture(GL_TEXTURE_2D, texture);
  shader->transmitUniform("inputTex0", 0);
  glDrawArrays(GL_QUADS, 0, 4);
  glBindVertexArray(NULL);
}

FrameBuffer::FrameBuffer()
{
  glGenFramebuffers(1, &m_fb);
}

FrameBuffer::~FrameBuffer()
{
  glDeleteFramebuffers(1, &m_fb);
}

void FrameBuffer::Bind(FrameBufferBindMode bufferMode /*= FBM_ReadWrite*/)
{
  BindFrameBuffer(m_fb, bufferMode);
}

void FrameBuffer::Unbind(FrameBufferBindMode bufferMode /*= FBM_ReadWrite*/)
{
  BindToScreen(bufferMode);
}

FrameBufferBindMode FrameBuffer::GetBindMode()
{
  GLint drawBuffer;
  GLint readBuffer;
  glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawBuffer);
  glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readBuffer);

  if (drawBuffer == m_fb && readBuffer == m_fb)
    return FBBM_ReadWrite;
  else if (drawBuffer == m_fb)
    return FBBM_Write;
  else if (readBuffer == m_fb)
    return FBBM_Read;
  else
    return FBBM_Unbound;
}

FrameBufferStatus FrameBuffer::GetStatus(FrameBufferBindMode bindMode)
{
  GLenum status;
  switch (bindMode)
  {
    case FBBM_Read:
      status = glCheckNamedFramebufferStatus(m_fb, GL_READ_FRAMEBUFFER);
      break;
    case FBBM_Write:
      status = glCheckNamedFramebufferStatus(m_fb, GL_DRAW_FRAMEBUFFER);
      break;
    case FBBM_ReadWrite:
      status = glCheckNamedFramebufferStatus(m_fb, GL_DRAW_FRAMEBUFFER);
      if(status == GL_FRAMEBUFFER_COMPLETE)
        glCheckNamedFramebufferStatus(m_fb, GL_READ_FRAMEBUFFER);
      break;
  } 
  switch(status)
  {
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
    case GL_FRAMEBUFFER_UNSUPPORTED:
      return FBS_INVALID_ATTACHMENT;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
      return FBS_MISSING_ATTACHMENT;
    case GL_FRAMEBUFFER_COMPLETE:
      return FBS_COMPLETE;
    default:
      return FBS_UNKNOWN_ERROR;
  }
}

void FrameBuffer::AttachColour(int location, GLuint texID)
{
  if (location >= FrameBuffer::MAX_COLOUR_ATTACHMENTS)
    throw std::exception("Attempt to bind texture to color attachment >= MAX_COLOUR_ATTACHMENTS");

  glNamedFramebufferTexture(m_fb, GL_COLOR_ATTACHMENT0 + location, texID, 0);
  AddColourAttachment(location);
  glDrawBuffers(colourAttachments.size(), colourAttachments.data());
}

void FrameBuffer::AttachDepth(GLuint texID)
{
  glNamedFramebufferTexture(m_fb, GL_DEPTH_ATTACHMENT, texID, 0);
}

void FrameBuffer::DetachColour(int location)
{
  glNamedFramebufferTexture(m_fb, GL_COLOR_ATTACHMENT0 + location, 0, 0);
  RemoveColourAttachment(location);
  glDrawBuffers(colourAttachments.size(), colourAttachments.data());
}

void FrameBuffer::DetachDepth()
{
  glNamedFramebufferTexture(m_fb, GL_DEPTH_ATTACHMENT, 0, 0);
}

int FrameBuffer::MAX_COLOUR_ATTACHMENTS = 8;

void FrameBuffer::BindFrameBuffer(GLuint buffer, FrameBufferBindMode bufferMode /*= FBBM_ReadWrite*/)
{
  switch (bufferMode)
  {
    case FBBM_Read:
      glBindFramebuffer(GL_READ_FRAMEBUFFER, buffer);
      break;
    case FBBM_Write:
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, buffer);
      break;
    case FBBM_ReadWrite:
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, buffer);
      glBindFramebuffer(GL_READ_FRAMEBUFFER, buffer);
      break;
  }
}

void FrameBuffer::AddColourAttachment(GLuint location)
{
  for (int i = 0; i < colourAttachments.size(); i++)
  {
    if (colourAttachments[i] == GL_COLOR_ATTACHMENT0 + location)
      return;
  }
  colourAttachments.push_back(GL_COLOR_ATTACHMENT0 + location);
}

void FrameBuffer::RemoveColourAttachment(GLuint location)
{
  for (int i = 0; i < colourAttachments.size(); i++)
  {
    if (colourAttachments[i] == GL_COLOR_ATTACHMENT0 + location)
      colourAttachments.erase(colourAttachments.begin() + i);
  }
}
