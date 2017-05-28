#ifndef IAnimatable_h__
#define IAnimatable_h__

#include "IAnimated.h"

/**
* @file AffineTransformable.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief An interface that allows the user to add functionality associated with an animated object.
*
*/


class IAnimatable : public IAnimated
{
public:

  /// <summary>
  /// Sets the active animation.
  /// </summary>
  /// <param name="animationName">Name of the animation.</param>
  void SetActiveAnimation(string const& animationName);

  /// <summary>
  /// Gets the name of the active animation.
  /// </summary>
  /// <returns></returns>
  string const& GetActiveAnimationName() const;

  /// <summary>
  /// Sets the active animation.
  /// </summary>
  /// <param name="animationIndex">Index of the animation.</param>
  virtual void SetActiveAnimation(int animationIndex) = 0;

  /// <summary>
  /// Gets the index of the active animation.
  /// </summary>
  /// <returns></returns>
  virtual int GetActiveAnimationIndex() const = 0;

  virtual void SetAnimationSection(float startTime, float sectionLength) = 0;

  virtual void SetAnimationStartTime(float time) = 0;

  virtual void SetAnimationSpeed(float speed) = 0;

};
#endif // IAnimatable_h__