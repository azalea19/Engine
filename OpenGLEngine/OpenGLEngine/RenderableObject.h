#ifndef RenderableObject_h__
#define RenderableObject_h__

#include "GL/glew.h"
#include "Types.h"
#include "IAnimatedRenderable.h"
#include "IAnimatable.h"
#include "IMeshCollection.h"

class Model;

enum TextureLocation
{
  TL_Diffuse = 0,
  TL_Alpha = 1,
};

enum DiffuseSource
{
  DS_MeshColour = 0,
  DS_VertexColour = 1,
  DS_Texture = 2,
};

enum BUFFER_TYPES
{
  BT_INDEX_BUFFER,
  BT_VERTEX_BUFFER,
  BT_NORMAL_BUFFER,
  BT_DIFFUSE_TEXCOORD_BUFFER,
  BT_ALPHA_TEXCOORD_BUFFER,
  BT_BONE_ID_BUFFER,
  BT_BONE_WEIGHT_BUFFER,
  BT_VERTEX_COLOUR_BUFFER,
  BT_NUM_BUFFERS //Gives back the number of buffer types
};

enum FillMode
{
  FM_Line,
  FM_Fill,
};

class RenderableObject : public IAnimatedRenderable, public IMeshCollection
{
public:

  RenderableObject(string const& name, string const& filename);
  ~RenderableObject();

  void Initialise();

  void Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time, int animationIndex) const;
  void Destroy();

  virtual int GetAnimationCount() const override;
  virtual int GetAnimationIndex(string const& animationName) const override;
  virtual string const& GetAnimationName(int animationIndex) const override;
  virtual IMesh const& GetMesh(int meshIndex) const override;
  virtual int GetMeshCount() const override;

private:

  Model* m_pModel;
  GLuint m_VAO;
  GLuint m_buffers[BT_NUM_BUFFERS];

  void RenderMesh(int meshIndex) const;
  void SetFillMode(FillMode fillMode) const;
  void BindMaterial(int meshIndex) const;
  void UpdateAnimation(float time, int activeAnimation) const;
  void UploadMatrices(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix) const;
};


#endif // RenderableObject_h__
