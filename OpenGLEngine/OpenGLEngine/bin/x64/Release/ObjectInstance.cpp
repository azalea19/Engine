#include "ObjectInstance.h"
#include "ShaderLibrary.h"
#include "RenderManager.h"

ObjectInstance::ObjectInstance(IRenderableObject* object, vec3 const& coords, vec3 const& scaleFactor, float yaw, float pitch)
  : m_pRenderableObject(object)
  , m_activeAnimation(-1)
{
  SetTransform(coords, yaw, pitch, 0, scaleFactor);
  RenderManager::GetInstance().AddObject(this);
}

void ObjectInstance::SetVisible(bool vis)
{
  m_visible = vis;
}

bool ObjectInstance::GetVisible() const
{
  return m_visible;
}

void ObjectInstance::Render(mat4 const& parentWorldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time)
{
  m_pRenderableObject->BindObject();
  for (int meshIndex = 0; meshIndex < m_pRenderableObject->GetMeshCount(); meshIndex++)
  {
    m_pRenderableObject->BindMesh(meshIndex);
    m_pRenderableObject->Render(parentWorldMatrix * GetWorldMatrix(), viewMatrix, projectionMatrix, time, m_activeAnimation);
  }
}



mat4 ObjectInstance::GetWorldMatrix() const
{
  return GetTransform();
}

std::vector<vec3> ObjectInstance::GetVertices(mat4 const& parentWorldMatrix) const
{
  std::vector<vec3> verts;
  verts = m_pRenderableObject->GetVertices();

  mat4 worldMatrix = parentWorldMatrix * GetWorldMatrix();

  vec4 temp;
  for (uint32_t i = 0; i < verts.size(); i++)
  {
    temp = vec4(verts[i], 1);
    temp = worldMatrix * temp;
    verts[i].x = temp.x;
    verts[i].y = temp.y;
    verts[i].z = temp.z;
  }

  return verts;
}

void ObjectInstance::SetActiveAnimation(int animationIndex)
{
  m_activeAnimation = animationIndex;
}

int ObjectInstance::GetActiveAnimationIndex() const
{
  return m_activeAnimation;
}

int ObjectInstance::GetAnimationCount() const
{
  return m_pRenderableObject->GetAnimationCount();
}

string const& ObjectInstance::GetAnimationName(int animationIndex) const
{
  return m_pRenderableObject->GetAnimationName(animationIndex);
}

int ObjectInstance::GetAnimationIndex(string const& animationName) const
{
  return m_pRenderableObject->GetAnimationIndex(animationName);
}

IRenderableObject const* ObjectInstance::GetRenderableObject() const
{
  return m_pRenderableObject;
}

