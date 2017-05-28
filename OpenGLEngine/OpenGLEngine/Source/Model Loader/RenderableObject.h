#ifndef RenderableObject_h__
#define RenderableObject_h__

#include "GL/glew.h"
#include "Types.h"
#include "IAnimatedRenderable.h"
#include "IAnimatable.h"
#include "IMeshCollection.h"
#include "IRenderableObject.h"
#include "GeometricPrimitives.h"


/**
* @file RenderableObject.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief 
*
*/

class Model;
class TriangleTree;

enum TextureLocation
{
  TL_Alpha = 0,
  TL_Diffuse0 = 1,
};

enum DiffuseSource
{
  DS_MeshColour = 0,
  DS_VertexColour = 1,
  DS_Texture = 2,
  DS_MultiTexture = 3,
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


class RenderableObject : public IRenderableObject
{
public:

  /// <summary>
  /// Initializes a new instance of the <see cref="RenderableObject"/> class.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <param name="filename">The filename.</param>
  RenderableObject(string const& name, string const& filename);

  /// <summary>
  /// Finalizes an instance of the <see cref="RenderableObject"/> class.
  /// </summary>
  ~RenderableObject();

  /// <summary>
  /// Initialises this instance.
  /// </summary>
  void Initialise() override;

  /// <summary>
  /// The render method.
  /// </summary>
  /// <param name="worldMatrix">The world matrix.</param>
  /// <param name="viewMatrix">The view matrix.</param>
  /// <param name="projectionMatrix">The projection matrix.</param>
  /// <param name="time">The time.</param>
  /// <param name="animationIndex">Index of the animation.</param>
  void Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time, int animationIndex) const override;
  
  /// <summary>
  /// Destroys this instance.
  /// </summary>
  void Destroy() override;

  /// <summary>
  /// Gets the animation count.
  /// </summary>
  /// <returns></returns>
  virtual int GetAnimationCount() const override;

  /// <summary>
  /// Gets the index of the animation.
  /// </summary>
  /// <param name="animationName">Name of the animation.</param>
  /// <returns>int</returns>
  virtual int GetAnimationIndex(string const& animationName) const override;
  
  /// <summary>
  /// Gets the name of the animation.
  /// </summary>
  /// <param name="animationIndex">Index of the animation.</param>
  /// <returns></returns>
  virtual string const& GetAnimationName(int animationIndex) const override;
  
  /// <summary>
  /// Gets the mesh.
  /// </summary>
  /// <param name="meshIndex">Index of the mesh.</param>
  /// <returns></returns>
  virtual IMesh const& GetMesh(int meshIndex) const override;
  
  /// <summary>
  /// Gets the mesh count.
  /// </summary>
  /// <returns></returns>
  virtual int GetMeshCount() const override;
  
  /// <summary>
  /// Binds the object.
  /// </summary>
  void BindObject() const override;
  
  /// <summary>
  /// Binds the mesh.
  /// </summary>
  /// <param name="meshIndex">Index of the mesh.</param>
  void BindMesh(int meshIndex) const override;
  
  /// <summary>
  /// Gets the bounding box of the renderable object.
  /// </summary>
  /// <returns></returns>
  const mAABB& GetBoundingBox() const override;

  const std::vector<mTriangle>& GetTriangleFaces() const override;

private:

  /// <summary>
  /// The model
  /// </summary>
  Model* m_pModel;

  /// <summary>
  /// The axis aligned bounding box
  /// </summary>
  mAABB m_boundingBox;

  /// <summary>
  /// The triangle faces of the renderable object
  /// </summary>
  std::vector<mTriangle> m_faces;

  /// <summary>
  /// The vertex array object
  /// </summary>
  GLuint m_VAO;

  /// <summary>
  /// The buffers
  /// </summary>
  GLuint m_buffers[BT_NUM_BUFFERS];

  TriangleTree* m_collisionTree;

  /// <summary>
  /// The bound mesh index
  /// </summary>
  mutable int boundMeshIndex;

  /// <summary>
  /// Binds the material.
  /// </summary>
  /// <param name="meshIndex">Index of the mesh.</param>
  void BindMaterial(int meshIndex) const;

  /// <summary>
  /// Sets the fill mode.
  /// </summary>
  /// <param name="fillMode">The fill mode.</param>
  void SetFillMode(FillMode fillMode) const;

  /// <summary>
  /// Updates the animation.
  /// </summary>
  /// <param name="time">The time.</param>
  /// <param name="activeAnimation">The active animation.</param>
  void UpdateAnimation(float time, int activeAnimation) const;

  /// <summary>
  /// Uploads the matrices.
  /// </summary>
  /// <param name="worldMatrix">The world matrix.</param>
  /// <param name="viewMatrix">The view matrix.</param>
  /// <param name="projectionMatrix">The projection matrix.</param>
  void UploadMatrices(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix) const;

  /// <summary>
  /// Creates the bounding box.
  /// </summary>
  void CreateBoundingBox();

  /// <summary>
  /// Gets the triangle faces.
  /// </summary>
  void CreateTriangleFaces();

  virtual bool Intersects(mOBB const& box) const override;

};


#endif // RenderableObject_h__
