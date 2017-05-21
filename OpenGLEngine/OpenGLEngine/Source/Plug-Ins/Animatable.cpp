#include "IAnimatable.h"



void IAnimatable::SetActiveAnimation(string const& animationName)
{
  return SetActiveAnimation(GetAnimationIndex(animationName));
}

string const& IAnimatable::GetActiveAnimationName() const
{
  return GetAnimationName(GetActiveAnimationIndex());
}
