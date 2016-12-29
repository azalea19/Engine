#pragma once
#include "Types.h"

//Interface to provide information about available animations
class IAnimated
{
public:
  virtual int GetAnimationCount() const = 0;
  virtual string const& GetAnimationName(int animationIndex) const = 0;
  virtual int GetAnimationIndex(string const& animationName) const = 0;
};