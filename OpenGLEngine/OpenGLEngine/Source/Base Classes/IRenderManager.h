#ifndef IRenderManager_h__
#define IRenderManager_h__


class IRenderManager
{

public:
  
  virtual void BeginRender() const = 0;
  virtual void EndRender() const = 0;
  virtual void Present(int camID) const =0;
  virtual void SetFillMode(int fillMode) const = 0;
  virtual void RenderObject(int camID, float time, int instanceHandle, int lightingApplied) const = 0;
  virtual void Initialise() const = 0;

};



#endif // IRenderManager_h__
