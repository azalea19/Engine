#ifndef ObjectInstance_h__
#define ObjectInstance_h__

#include "RenderableObject.h"
#include "IRenderable.h"
#include "AffineTransformable.h"


/**
* @file   ObjectInstance.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief  The object instance struct.
*
* The object instance class stores the data relating to a particular instance of a model.
*/


class ObjectInstance : public IRenderable, public IAnimatable, public AffineTransformable
{

public: 

  /// <summary>
  /// Initializes a new instance of the <see cref="ObjectInstance"/> struct.
  /// </summary>
  /// <param name="object">The object.</param>
  /// <param name="coords">The coords.</param>
  /// <param name="scaleFactor">The scale factor.</param>
  /// <param name="yaw">The yaw.</param>
  /// <param name="pitch">The pitch.</param>
  ObjectInstance(IRenderableObject* object, vec3 const& coords = glm::vec3(0, 0, 0), vec3 const& scaleFactor = vec3(1, 1, 1), float yaw = 0, float pitch = 0);

  /// <summary>
  /// Gets the vertices.
  /// </summary>
  /// <param name="parentModelMatrix">The parent model matrix.</param>
  /// <returns>std::vector<vec3></returns>
  std::vector<vec3> GetVertices(mat4 const& parentModelMatrix = mat4()) const;

  /// <summary>
  /// Gets the world matrix.
  /// </summary>
  /// <returns>mat4</returns>
  mat4 GetWorldMatrix() const;

  /// <summary>
  /// The render method.
  /// </summary>
  /// <param name="worldMatrix">The world matrix.</param>
  /// <param name="viewMatrix">The view matrix.</param>
  /// <param name="projectionMatrix">The projection matrix.</param>
  /// <param name="time">The time.</param>
  virtual void Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time = 0) override;

  /// <summary>
  /// Sets the active animation.
  /// </summary>
  /// <param name="animationIndex">Index of the animation.</param>
  virtual void SetActiveAnimation(int animationIndex) override;

  /// <summary>
  /// Gets the index of the active animation.
  /// </summary>
  /// <returns>int</returns>
  virtual int GetActiveAnimationIndex() const override;

  /// <summary>
  /// Gets the animation count.
  /// </summary>
  /// <returns>int</returns>
  virtual int GetAnimationCount() const override;

  /// <summary>
  /// Gets the name of the animation.
  /// </summary>
  /// <param name="animationIndex">Index of the animation.</param>
  /// <returns>string</returns>
  virtual string const& GetAnimationName(int animationIndex) const override;

  /// <summary>
  /// Gets the index of the animation.
  /// </summary>
  /// <param name="animationName">Name of the animation.</param>
  /// <returns>int</returns>
  virtual int GetAnimationIndex(string const& animationName) const override;

  /// <summary>
  /// Gets the renderable object.
  /// </summary>
  /// <returns>IRenderableObject</returns>
  IRenderableObject const* GetRenderableObject() const;

  /// <summary>
  /// Sets whether the instance is visible.
  /// </summary>
  /// <param name="vis">if set to <c>true</c> [vis].</param>
  void SetVisible(bool vis);

  /// <summary>
  /// Gets whether the object is visible.
  /// </summary>
  /// <returns>bool</returns>
  bool GetVisible() const;
  
  /// <summary>
  /// Gets the oriented bounding box of the object instance.
  /// </summary>
  /// <returns></returns>
  mOBB GetBoundingBox() const;
  
 
  /// <summary>
  /// Determines whether box intersects any triangles in the object instance.
  /// </summary>
  /// <param name="box">The box.</param>
  /// <returns></returns>
  bool Intersects(mAABB const& box);

  /// <summary>
  /// Determines whether box intersects any triangles in the object instance.
  /// </summary>
  /// <param name="box">The box.</param>
  /// <returns></returns>
  bool Intersects(mOBB const& box);

private:

  /// <summary>
  /// The renderable object
  /// </summary>
  IRenderableObject * m_pRenderableObject;

  /// <summary>
  /// The active animation
  /// </summary>
  int m_activeAnimation;

  /// <summary>
  /// Whether the instance is visible
  /// </summary>
  bool m_visible = true;

};

#endif //ObjectInstance_h__