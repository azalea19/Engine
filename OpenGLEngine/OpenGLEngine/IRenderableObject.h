#ifndef IRenderableObject_h__
#define IRenderableObject_h__

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

class IRenderableObject : public IAnimatedRenderable, public IMeshCollection
{

public:

  virtual void Initialise() = 0;
  virtual void Destroy() =0;
  virtual void BindObject() const = 0;
  virtual void BindMesh(int meshIndex) const = 0;
  virtual void Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time, int animationIndex) const = 0;

};


#endif // RenderableObject_h__
