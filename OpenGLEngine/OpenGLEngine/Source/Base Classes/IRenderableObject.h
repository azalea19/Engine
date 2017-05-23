#ifndef IRenderableObject_h__
#define IRenderableObject_h__

#include "GL/glew.h"
#include "Types.h"
#include "IAnimatedRenderable.h"
#include "IAnimatable.h"
#include "IMeshCollection.h"
#include "GeometricPrimitives.h"

/**
* @file RenderableObject.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief An interface that allows the user to add functionality associated with a renderable object.
*
*/


class Model;



enum FillMode
{
  FM_Line,
  FM_Fill,
};

class IRenderableObject : public IAnimatedRenderable, public IMeshCollection
{

public:

  /// <summary>
  /// Initialises this instance.
  /// </summary>
  virtual void Initialise() = 0;
  
  /// <summary>
  /// Destroys this instance.
  /// </summary>
  virtual void Destroy() = 0;

  /// <summary>
  /// Binds the object.
  /// </summary>
  virtual void BindObject() const = 0;

  /// <summary>
  /// Binds the mesh.
  /// </summary>
  /// <param name="meshIndex">Index of the mesh.</param>
  virtual void BindMesh(int meshIndex) const = 0;


  /// <summary>
  /// The render method.
  /// </summary>
  /// <param name="worldMatrix">The world matrix.</param>
  /// <param name="viewMatrix">The view matrix.</param>
  /// <param name="projectionMatrix">The projection matrix.</param>
  /// <param name="time">The time.</param>
  /// <param name="animationIndex">Index of the animation.</param>
  virtual void Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time, int animationIndex) const = 0;

  virtual mAABB GetBoundingBox() const = 0;

  virtual std::vector<mTriangle> GetTriangleFaces() const = 0;

};


#endif // RenderableObject_h__
