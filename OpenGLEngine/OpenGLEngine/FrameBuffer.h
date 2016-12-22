#ifndef FrameBuffer_h__
#define FrameBuffer_h__

#include "GL/glew.h"
#include "Types.h"

enum FrameBufferBindMode
{
  FBBM_Read,
  FBBM_Write,
  FBBM_ReadWrite,
  FBBM_Unbound,
};

enum FrameBufferStatus
{
  FBS_COMPLETE,
  FBS_INVALID_ATTACHMENT,
  FBS_INCONSISTENT_DIMENSIONS,
  FBS_MISSING_ATTACHMENT,
  FBS_UNKNOWN_ERROR,
};

class FrameBuffer
{
public:
  static GLuint FSQuadVAO;
  static void Initialize();
  static void BindToScreen(FrameBufferBindMode bufferMode = FBBM_ReadWrite);
  static void Display(GLuint texture);

	FrameBuffer();
	~FrameBuffer();

  void Bind(FrameBufferBindMode bufferMode = FBBM_ReadWrite);
  void Unbind(FrameBufferBindMode bufferMode = FBBM_ReadWrite);
  FrameBufferBindMode GetBindMode();
  FrameBufferStatus GetStatus(FrameBufferBindMode bindMode = FBBM_ReadWrite);

  void AttachColour(int location, GLuint texID);
  void AttachDepth(GLuint texID);

  void DetachColour(int location);
  void DetachDepth();


private:
  GLuint m_fb = 0;
  std::vector<GLuint> colourAttachments;
  static int MAX_COLOUR_ATTACHMENTS;

  static void BindFrameBuffer(GLuint buffer, FrameBufferBindMode bufferMode = FBBM_ReadWrite);
  void AddColourAttachment(GLuint location);
  void RemoveColourAttachment(GLuint location);
};


#endif