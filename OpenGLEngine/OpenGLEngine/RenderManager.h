#ifndef RenderManager_h__
#define RenderManager_h__

#include "Singleton.h"
#include <unordered_map>
#include <vector>
#include "IRenderable.h"
#include "IRenderableObject.h"


/**
* @file RenderManager.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief The render manager allows for managed (batched) rendering which reduces the copying of index, normal, UV and vertex buffers.
*/

class RenderableObject;
class ObjectInstance;

class RenderManager : public Singleton<RenderManager>, public IRenderable
{
public:

  /// <summary>
  /// Adds the object.
  /// </summary>
  /// <param name="pObject">The p object.</param>
  void AddObject(ObjectInstance const* pObject);

  /// <summary>
  /// Removes the object.
  /// </summary>
  /// <param name="pObject">The p object.</param>
  void RemoveObject(ObjectInstance const* pObject);

  /// <summary>
  /// The render method.
  /// </summary>
  /// <param name="worldMatrix">The world matrix.</param>
  /// <param name="viewMatrix">The view matrix.</param>
  /// <param name="projectionMatrix">The projection matrix.</param>
  /// <param name="time">The time.</param>
  virtual void Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time) override;

  /// <summary>
  /// Gets the frame rate.
  /// </summary>
  /// <returns></returns>
  float GetFrameRate() const;

private:

  /// <summary>
  /// The object map
  /// </summary>
  std::unordered_map <IRenderableObject const*, std::vector<ObjectInstance const*>> m_objectMap;

  /// <summary>
  /// The render times
  /// </summary>
  std::vector<float> m_renderTimes;

  /// <summary>
  /// The frame rate
  /// </summary>
  float m_frameRate;

  /// <summary>
  /// Updates the frame rate.
  /// </summary>
  /// <param name="time">The time.</param>
  void UpdateFrameRate(float time);

};
#endif // RenderManager_h__