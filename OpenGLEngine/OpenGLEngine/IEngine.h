#ifndef IEngine_h__
#define IEngine_h__

#include "types.h"

enum GraphicsAPI
{
  API_OPEN_GL,
  API_DIRECT_X,
  API_VULKAN
};

enum WindowAPI
{
  API_SDL,
  API_GLFW,
  API_FREEGLUT
};

class IEngine 
{
public:

  virtual ~IEngine() = 0 {}
  virtual void Initialise(int screenWidth, int screenHeight) = 0;
  virtual void SetScreenDimensions() = 0;
  virtual void BeginRender() = 0;
  virtual void EndRender() = 0;
  virtual bool BeginUpdate() = 0;
  virtual void EndUpdate() = 0;

};
#endif // IEngine_h__
