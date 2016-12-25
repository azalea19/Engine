#ifndef RenderableObject_h__
#define RenderableObject_h__

#include "GL/glew.h"
#include "Types.h"

class Model;

enum TextureLocation
{
  TL_Diffuse = 0,
};

enum DiffuseSource
{
  DS_MeshColour = 0b00,
  DS_VertexColour = 0b01,
  DS_Texture = 0b10,
};

enum BUFFER_TYPES
{
  BT_INDEX_BUFFER,
  BT_VERTEX_BUFFER,
  BT_NORMAL_BUFFER,
  BT_TEXCOORD_BUFFER,
  BT_BONE_ID_BUFFER,
  BT_BONE_WEIGHT_BUFFER,
  BT_VERTEX_COLOUR_BUFFER,
  BT_NUM_BUFFERS //Gives back the number of buffer types (5)
};

enum FillMode
{
  FM_Line,
  FM_Fill,
};

class RenderableObject
{
public:

  RenderableObject();
  RenderableObject(string const& name, string const& filename);
  ~RenderableObject();

  void Initialise();

  void Render( mat4 worldMatrix, mat4 viewMatrix, mat4 projectionMatrix, FillMode fillMode = FM_Fill, DiffuseSource diffuseSource = DS_Texture, int animationIndex = -1, float time = 0);

  void Destroy();

private:

  Model* m_pModel;
  GLuint m_VAO;
  GLuint m_buffers[BT_NUM_BUFFERS];

  void RenderMesh(int meshIndex, DiffuseSource diffuseSource);
  void SetFillMode(FillMode fillMode);
  void BindMaterial(int meshIndex, DiffuseSource diffuseSource);
  void UpdateAnimation(int animationIndex, float time);
  void UploadMatrices(mat4 worldMatrix, mat4 viewMatrix, mat4 projectionMatrix);
};


#endif // RenderableObject_h__
