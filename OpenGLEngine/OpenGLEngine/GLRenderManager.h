#ifndef GLRenderManager_h__
#define GLRenderManager_h__

#include "IRenderManager.h"

class GLRenderManager : public IRenderManager
{
  
public:

  GLRenderManager();

  virtual void BeginRender() const override;


  virtual void EndRender() const override;


  virtual void Present(int camID) const override;


  virtual void SetFillMode(int fillMode) const override;


  virtual void RenderObject(int camID, float time, int instanceHandle, int lightingApplied) const override;


  virtual void Initialise() const;

};

#endif // GLRenderManager_h__
