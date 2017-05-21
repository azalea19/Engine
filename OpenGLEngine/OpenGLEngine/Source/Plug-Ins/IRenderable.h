#ifndef Renderable_h__
#define Renderable_h__

#include "Types.h"

/**
* @file Renderable.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief An interface that allows the user to add functionality associated with a renderable object.
*
*/

class IRenderable
{

public:

  /// <summary>
  /// The render method.
  /// </summary>
  /// <param name="worldMatrix">The world matrix.</param>
  /// <param name="viewMatrix">The view matrix.</param>
  /// <param name="projectionMatrix">The projection matrix.</param>
  /// <param name="time">The time.</param>
  virtual void Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time) = 0;

};

#endif // Renderable_h__
