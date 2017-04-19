#ifndef ObjectInstance_h__
#define ObjectInstance_h__

#include "RenderableObject.h"
#include "IRenderable.h"
#include "AffineTransformable.h"


/**
* @file   ObjectInstance.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The object instance struct.
*
* The object instance class stores the data relating to a particular instance of a model.
*/


struct ObjectInstance : public IRenderable, public IAnimatable, public AffineTransformable
{

public: 

	ObjectInstance(IRenderableObject* object, vec3 const& coords = glm::vec3(0, 0, 0), vec3 const& scaleFactor = vec3(1, 1, 1), float yaw = 0, float pitch = 0);

	std::vector<vec3> GetVertices(mat4 const& parentModelMatrix = mat4()) const;

	mat4 GetWorldMatrix() const;

  virtual void Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time = 0) override;

  virtual void SetActiveAnimation(int animationIndex) override;
  virtual int GetActiveAnimationIndex() const override;
  virtual int GetAnimationCount() const override;
  virtual string const& GetAnimationName(int animationIndex) const override;
  virtual int GetAnimationIndex(string const& animationName) const override;

  IRenderableObject const* GetRenderableObject() const;

  void SetVisible(bool vis);

  bool GetVisible() const;
  

private:

	IRenderableObject * m_pRenderableObject;		
  int m_activeAnimation;
  bool m_visible = true;

};

#endif //ObjectInstance_h__