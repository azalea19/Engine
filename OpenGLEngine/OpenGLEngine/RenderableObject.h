#ifndef RenderableObject_h__
#define RenderableObject_h__

#include "GL/glew.h"
#include "Types.h"

class Model;

enum BUFFER_TYPES
{
  BT_INDEX_BUFFER,
  BT_VERTEX_BUFFER,
  BT_NORMAL_BUFFER,
  BT_TEXCOORD_BUFFER,
  BT_BONE_ID_BUFFER,
  BT_BONE_WEIGHT_BUFFER,
  BT_NUM_BUFFERS //Gives back the number of buffer types (5)
};

class RenderableObject
{
public:

  RenderableObject();
  RenderableObject(string const& name, string const& filename);
  ~RenderableObject();

  void UpdateBones(float time);

  void Initialise();

  void Render( mat4 worldMatrix, mat4 viewMatrix, mat4 projectionMatrix, float time = 0);

  void Destroy();

private:

  Model* m_pModel;
  GLuint m_VAO;
  GLuint m_buffers[BT_NUM_BUFFERS];

};


#endif // RenderableObject_h__
