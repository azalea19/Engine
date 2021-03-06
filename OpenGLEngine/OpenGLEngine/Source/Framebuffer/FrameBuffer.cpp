#include "FrameBuffer.h"
#include <exception>
#include "Types.h"
#include "Shader.h"
#include "ShaderLibrary.h"
#include "Screen.h"
#include <memory>

/// <summary>
/// The fs quad vao{CC2D43FA-BBC4-448A-9D0B-7B57ADF2655C}
/// </summary>
GLuint FrameBuffer::FSQuadVAO;

void FrameBuffer::Initialize()
{
  glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &FrameBuffer::MAX_COLOUR_ATTACHMENTS);

  static float offsetX = 0.5f / GetScreenDimensions().x;
  static float offsetY = 0.5f / GetScreenDimensions().y;

  static vec2 verts[4] =
  {
    vec2(-1, 1), vec2(1, 1),
    vec2(1, -1), vec2(-1, -1)
  };

  static vec2 uvs[4] =
  {

    vec2(offsetX, 1 - offsetY), vec2(1 - offsetX, 1 - offsetY),
    vec2(1 - offsetX, offsetY), vec2(offsetX, offsetY)
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
  glEnableVertexAttribArray(AL_DiffuseTexCoords);
  glVertexAttribPointer(AL_DiffuseTexCoords, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindVertexArray(NULL);
}

void FrameBuffer::BindToScreen(FrameBufferBindMode bufferMode /*= FBM_ReadWrite*/)
{
  BindFrameBuffer(0, bufferMode);
}

void FrameBuffer::Display(GLuint texture)
{
  std::unique_ptr<IShader> const& shader = ShaderLibrary::GetInstance().GetShader("TextureDisplay");

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  FrameBuffer::BindToScreen();
  shader->Bind();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBindVertexArray(FrameBuffer::FSQuadVAO);
  glActiveTexture(GL_TEXTURE0 + 0);
  glBindTexture(GL_TEXTURE_2D, texture);
  shader->TransmitUniform("inputTex0", 0);
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
  FrameBufferBindMode currentBindMode = GetBindMode();
  FrameBufferBindMode checkMode = FrameBufferBindMode(currentBindMode & bindMode);

  if (checkMode == FBBM_Unbound)
    return FBS_Unbound;

  GLenum status;
  switch (checkMode)
  {
    case FBBM_Read:
      status = glCheckFramebufferStatus(GL_READ_FRAMEBUFFER);
      break;
    case FBBM_Write:
      status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
      break;
    case FBBM_ReadWrite:
      status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
      if(status == GL_FRAMEBUFFER_COMPLETE)
        glCheckFramebufferStatus(GL_READ_FRAMEBUFFER);
      break;
  } 
  switch(status)
  {
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
    case GL_FRAMEBUFFER_UNSUPPORTED:
      return FBS_InvalidAttachment;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
      return FBS_MissingAttachment;
    case GL_FRAMEBUFFER_COMPLETE:
      return FBS_Complete;
    default:
      return FBS_UnknownError;
  }
}

void FrameBuffer::AttachColour(int location, GLuint texID)
{
  FrameBufferBindMode bindMode = GetBindMode();
  
  if (bindMode == FBBM_Unbound)
    throw std::exception("Attempt to attach texture to FrameBuffer that is not bound");

  if (location >= FrameBuffer::MAX_COLOUR_ATTACHMENTS)
    throw std::exception("Attempt to attach texture to color attachment >= MAX_COLOUR_ATTACHMENTS");

  if(bindMode & FBBM_Read)
    glFramebufferTexture(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + location, texID, 0);
  else
    glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + location, texID, 0);
  
  AddColourAttachment(location);
  glDrawBuffers(colourAttachments.size(), colourAttachments.data());
}

void FrameBuffer::AttachDepth(GLuint texID)
{
  FrameBufferBindMode bindMode = GetBindMode();

  if (bindMode == FBBM_Unbound)
    throw std::exception("Attempt to attach texture to FrameBuffer that is not bound");

  if (bindMode & FBBM_Read)
    glFramebufferTexture(GL_READ_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texID, 0);
  else
    glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texID, 0);
}

void FrameBuffer::DetachColour(int location)
{
  FrameBufferBindMode bindMode = GetBindMode();

  if (bindMode == FBBM_Unbound)
    throw std::exception("Attempt to detach texture from FrameBuffer that is not bound");

  if (bindMode & FBBM_Read)
    glFramebufferTexture(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + location, 0, 0);
  else
    glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + location, 0, 0);

  RemoveColourAttachment(location);
  glDrawBuffers(colourAttachments.size(), colourAttachments.data());
}

void FrameBuffer::DetachDepth()
{
  FrameBufferBindMode bindMode = GetBindMode();

  if (bindMode == FBBM_Unbound)
    throw std::exception("Attempt to attach texture to FrameBuffer that is not bound");

  if (bindMode & FBBM_Read)
    glFramebufferTexture(GL_READ_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, 0, 0);
  else
    glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, 0, 0);
}

/// <summary>
/// The maximum colour attachments{CC2D43FA-BBC4-448A-9D0B-7B57ADF2655C}
/// </summary>
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
