#ifndef FrameBuffer_h__
#define FrameBuffer_h__

#include "GL/glew.h"
#include "Types.h"

/**
* @file FrameBuffer.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief The frame buffer allows for higher level post processing effects.
* 
* The frame buffer takes the output rendered to the window and creates a texture (texture buffer) for the data
* such as normals and depth information (known as rendering to a texture / off screen rendering).
* By creating texture buffers to store data for use in the shaders we can create higher level effects
* that are applied to the screen output to a two dimensional texture with three dimensional data (depth, normals etc).
* See: 
* https://learnopengl.com/#!Advanced-OpenGL/Framebuffers
* http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/
*/

enum FrameBufferBindMode
{
  FBBM_Unbound = 0,
  FBBM_Read = 0b01,
  FBBM_Write = 0b10,
  FBBM_ReadWrite = FBBM_Read | FBBM_Write,
};

enum FrameBufferStatus
{
  FBS_Complete,
  FBS_InvalidAttachment,
  FBS_InconsistentDimensions,
  FBS_MissingAttachment,
  FBS_Unbound,
  FBS_UnknownError,
};

class FrameBuffer
{
public:

  static GLuint FSQuadVAO;

  /// <summary>
  /// Initializes this instance.
  /// </summary>
  static void Initialize();

  /// <summary>
  /// Binds the frame buffer to the screen.
  /// </summary>
  /// <param name="bufferMode">The buffer mode.</param>
  static void BindToScreen(FrameBufferBindMode bufferMode = FBBM_ReadWrite);

  /// <summary>
  /// Displays the specified texture to the screen.
  /// </summary>
  /// <param name="texture">The texture.</param>
  static void Display(GLuint texture);


  /// <summary>
  /// Initializes a new instance of the <see cref="FrameBuffer"/> class.
  /// </summary>
  FrameBuffer();
	
  /// <summary>
  /// Finalizes an instance of the <see cref="FrameBuffer"/> class.
  /// </summary>
  ~FrameBuffer();

  /// <summary>
  /// Binds the specified buffer mode.
  /// </summary>
  /// <param name="bufferMode">The buffer mode.</param>
  void Bind(FrameBufferBindMode bufferMode = FBBM_ReadWrite);
  
  /// <summary>
  /// Unbinds the specified buffer mode.
  /// </summary>
  /// <param name="bufferMode">The buffer mode.</param>
  void Unbind(FrameBufferBindMode bufferMode = FBBM_ReadWrite);
  
  /// <summary>
  /// Gets the bind mode.
  /// </summary>
  /// <returns>FrameBufferBindMode</returns>
  FrameBufferBindMode GetBindMode();
  
  /// <summary>
  /// Gets the status of the frame buffer.
  /// </summary>
  /// <param name="bindMode">The bind mode.</param>
  /// <returns></returns>
  FrameBufferStatus GetStatus(FrameBufferBindMode bindMode = FBBM_ReadWrite);

  /// <summary>
  /// Attaches the color buffer.
  /// </summary>
  /// <param name="location">The location.</param>
  /// <param name="texID">The texture identifier.</param>
  void AttachColour(int location, GLuint texID);
  
  /// <summary>
  /// Attaches the depth buffer.
  /// </summary>
  /// <param name="texID">The texture identifier.</param>
  void AttachDepth(GLuint texID);

  /// <summary>
  /// Detaches the color buffer.
  /// </summary>
  /// <param name="location">The location.</param>
  void DetachColour(int location);

  /// <summary>
  /// Detaches the depth buffer.
  /// </summary>
  void DetachDepth();


private:


  /// <summary>
  /// The frame buffer.
  /// </summary>
  GLuint m_fb = 0;

  /// <summary>
  /// The color attachments
  /// </summary>
  std::vector<GLuint> colourAttachments;

  static int MAX_COLOUR_ATTACHMENTS;

  /// <summary>
  /// Binds the frame buffer.
  /// </summary>
  /// <param name="buffer">The buffer.</param>
  /// <param name="bufferMode">The buffer mode.</param>
  static void BindFrameBuffer(GLuint buffer, FrameBufferBindMode bufferMode = FBBM_ReadWrite);
  
  /// <summary>
  /// Adds the color attachment.
  /// </summary>
  /// <param name="location">The location.</param>
  void AddColourAttachment(GLuint location);
  
  /// <summary>
  /// Removes the color attachment.
  /// </summary>
  /// <param name="location">The location.</param>
  void RemoveColourAttachment(GLuint location);

};


#endif