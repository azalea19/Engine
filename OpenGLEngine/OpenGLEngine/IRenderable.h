#ifndef Renderable_h__
#define Renderable_h__

#include "Types.h"

class IRenderable
{
public:

  virtual void Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time) const
  {}

private:

};

#endif // Renderable_h__
