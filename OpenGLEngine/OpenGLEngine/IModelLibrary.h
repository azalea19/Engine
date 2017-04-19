#ifndef IModelLibrary_h__
#define IModelLibrary_h__

#include "types.h"
#include "ObjectInstance.h"

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

class IModelLibrary
{

public:
 
  virtual void Initialise() = 0;
  virtual ~IModelLibrary() = 0 {}
  virtual void AddModel(string const& modelName, string const& filePath, bool normalised) = 0;
  virtual ObjectInstance* GetObjectInstance(string const& modelName) const = 0;

private:


};
#endif // IModelLibrary_h__
