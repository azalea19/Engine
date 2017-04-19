#ifndef IAnimatedRenderable_h__
#define IAnimatedRenderable_h__

#include "IRenderable.h"
#include "IAnimated.h"

/**
* @file IAnimatedRenderable.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief An interface that allows the user to add functionality associated with an animated renderable object.
*
*/

class IAnimatedRenderable : public IAnimated
{


public:

  void RenderB(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time) const;


  /// <summary>
  /// The render method of an animated renderable object.
  /// </summary>
  /// <param name="worldMatrix">The world matrix.</param>
  /// <param name="viewMatrix">The view matrix.</param>
  /// <param name="projectionMatrix">The projection matrix.</param>
  /// <param name="time">The time.</param>
  /// <param name="animationIndex">Index of the animation.</param>
  virtual void Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time, int animationIndex) const = 0;

};

#endif // IAnimatedRenderable_h__
