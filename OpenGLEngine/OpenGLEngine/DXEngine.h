#ifndef DXEngine_h__
#define DXEngine_h__

#include "IEngine.h"


class DXEngine : public IEngine
{

public:

  static IEngine* Create();


  virtual void Initialise(int screenWidth, int screenHeight) override;


  virtual void SetScreenDimensions() override;


  virtual void BeginRender() override;


  virtual void EndRender() override;


  virtual bool BeginUpdate() override;


  virtual void EndUpdate() override;


private:

  DXEngine();

  virtual ~DXEngine() override;

};

#endif // DXEngine_h__
