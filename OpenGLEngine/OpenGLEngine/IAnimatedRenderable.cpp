#include "IAnimatedRenderable.h"


void IAnimatedRenderable::RenderB(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time) const
{
  Render(worldMatrix, viewMatrix, projectionMatrix, time, -1);
}
