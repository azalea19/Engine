#ifndef Renderer_h__
#define Renderer_h__

#include "Singleton.h"
#include "IRenderManager.h"
#include <memory>

class Renderer : public Singleton<Renderer>
{

public:

  void BeginRender() const;
  void EndRender() const;
  void Present(int camID) const;
  void SetFillMode(int fillMode) const;
  void RenderObject(int camID, float time, int instanceHandle, int lightingApplied) const;

  void Initialise(IRenderManager* renderManager);

private:

  std::unique_ptr<IRenderManager> renderer;

};




#endif // Renderer_h__
