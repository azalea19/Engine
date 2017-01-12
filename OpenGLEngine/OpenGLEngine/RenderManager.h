#ifndef RenderManager_h__
#define RenderManager_h__

#include "Singleton.h"
#include <unordered_map>
#include <vector>
#include "IRenderable.h"

class RenderableObject;
struct ObjectInstance;

class RenderManager : public Singleton<RenderManager>, public IRenderable
{
public:

  void AddObject(ObjectInstance const* pObject);
  void RemoveObject(ObjectInstance const* pObject);
  virtual void Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time) override;
  float GetFrameRate() const;
private:
  std::unordered_map < RenderableObject const*, std::vector<ObjectInstance const*>> m_objectMap;
  std::vector<float> m_renderTimes;
  float m_frameRate;

  void UpdateFrameRate(float time);

};
#endif // RenderManager_h__