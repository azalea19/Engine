#ifndef IAnimatable_h__
#define IAnimatable_h__

#include "IAnimated.h"

class IAnimatable : public IAnimated
{
public:
  void SetActiveAnimation(string const& animationName);
  string const& GetActiveAnimationName() const;
  virtual void SetActiveAnimation(int animationIndex) = 0;
  virtual int GetActiveAnimationIndex() const = 0;
};
#endif // IAnimatable_h__