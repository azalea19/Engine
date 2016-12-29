#ifndef IAnimatedRenderable_h__
#define IAnimatedRenderable_h__

#include "IRenderable.h"
#include "IAnimated.h"

class IAnimatedRenderable : public IAnimated
{

public:

  void RenderB(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time) const;


  virtual void Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time, int animationIndex) const = 0;

private:

};

#endif // IAnimatedRenderable_h__
