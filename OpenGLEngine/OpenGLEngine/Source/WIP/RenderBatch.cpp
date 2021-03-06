#include "RenderBatch.h"
#include "ObjectInstance.h"
#include "Utility.h"
#include "IMesh.h"

void RenderBatch::AddObject(ObjectInstance const* pObject)
{
 IRenderableObject const* rObject = pObject->GetRenderableObject();
  auto i = m_objectMap.find(rObject);
  if (i == m_objectMap.end())
    m_objectMap.emplace(rObject, CreateVector(pObject));
  else
    i->second.push_back(pObject);
}

void RenderBatch::RemoveObject(ObjectInstance const* pObject)
{
  IRenderableObject const* rObject = pObject->GetRenderableObject();
  auto i = m_objectMap.find(rObject);
  if (i != m_objectMap.end())
  {
    std::vector<ObjectInstance const*>& instances = i->second;
    for (int j = 0; j < instances.size(); j++)
    {
      if (instances[j] == pObject)
      {
        instances.erase(instances.begin() + j);
        break;
      }
    }
  }
}

void RenderBatch::Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time)
{
  int verticesDrawn = 0;
  for (auto i : m_objectMap)
  {
    IRenderableObject const* pObject = i.first;
    std::vector<ObjectInstance const*>& instances = i.second;
    pObject->BindObject();
    for (int meshIndex = 0; meshIndex < pObject->GetMeshCount(); meshIndex++)
    {
      pObject->BindMesh(meshIndex);
      for (int instance = 0; instance < instances.size(); instance++)
      {
        if (instances[instance]->GetVisible())
        {
          verticesDrawn += pObject->GetMesh(meshIndex).GetVertexCount();
          mat4 worldMatrix = instances[instance]->GetTransform();
          int animationIndex = instances[instance]->GetActiveAnimationIndex();
          pObject->Render(worldMatrix, viewMatrix, projectionMatrix, time, animationIndex);
        }
      }
    }
  }
  UpdateFrameRate(time);
}

float RenderBatch::GetFrameRate() const
{
  return m_frameRate;
}

void RenderBatch::UpdateFrameRate(float time)
{
  if (m_renderTimes.size() == 60)
    m_renderTimes.erase(m_renderTimes.begin());
  m_renderTimes.push_back(time);

  float totalTime = m_renderTimes[m_renderTimes.size() - 1] - m_renderTimes[0];

  m_frameRate = m_renderTimes.size() / totalTime;
}
