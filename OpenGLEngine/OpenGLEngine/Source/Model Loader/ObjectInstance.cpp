#include "ObjectInstance.h"
#include "ShaderLibrary.h"
#include "RenderBatch.h"
#include "PrimitiveCollisions.h"
#include "TriangleTree.h"
#include "MMath.h"

ObjectInstance::ObjectInstance(IRenderableObject* object, vec3 const& coords, vec3 const& scaleFactor, float yaw, float pitch)
  : m_pRenderableObject(object)
  , m_activeAnimation(-1)
  , m_animationSectionStart(0)
  , m_animationSectionLength(FLT_MAX)
  , m_animationSpeed(1)
{
  SetTransform(coords, yaw, pitch, 0, scaleFactor);
}

void ObjectInstance::SetVisible(bool vis)
{
  m_visible = vis;
}

bool ObjectInstance::GetVisible() const
{
  return m_visible;
}

mOBB ObjectInstance::GetBoundingBox() const
{
  return GetTransform() * m_pRenderableObject->GetBoundingBox();
}

//Gets a ws axis aligned bounding box from the OBB
mAABB ObjectInstance::GetAlignedBoundingBox()
{
  mOBB result = GetBoundingBox();

  mAABB finalBox;
  finalBox.min = result.corners[0];
  finalBox.max = result.corners[0];
  for (int i = 1; i < 8; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      finalBox.min[j] = mMin(finalBox.min[j], result.corners[i][j]);
      finalBox.max[j] = mMax(finalBox.max[j], result.corners[i][j]);
    }
  }

  return finalBox;
}

//Expects a box in world space coords
bool ObjectInstance::Intersects(mAABB const & box)
{
  //Transform the box in to the model space of the object instance
  return Intersects(inverse(GetTransform()) * box);
}

//Expects box in model space
bool ObjectInstance::Intersects(mOBB const & box)
{
  return m_pRenderableObject->Intersects(box);
}


mat4 ObjectInstance::GetTransform() const
{
  return AffineTransformable::GetTransform() * m_baseTransform.GetTransform();
}

void ObjectInstance::SetBaseTransform(vec3 translation, float yaw, float pitch, float roll, vec3 scale)
{
  m_baseTransform.SetTranslation(translation);
  m_baseTransform.SetOrientation(yaw, pitch, roll);
  m_baseTransform.SetScale(scale);
}

void ObjectInstance::SetAnimationSection(float startTime, float sectionLength)
{
  m_animationSectionStart = startTime;
  m_animationSectionLength = sectionLength;
}

void ObjectInstance::SetAnimationStartTime(float time)
{
  m_animationStartTime = time;
}

void ObjectInstance::SetAnimationSpeed(float speed)
{
  m_animationSpeed = speed;
}

void ObjectInstance::Render(mat4 const& parentWorldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time)
{
  float animationTime = fmod(((time - m_animationStartTime) * m_animationSpeed), m_animationSectionLength);
  m_pRenderableObject->BindObject();
  for (int meshIndex = 0; meshIndex < m_pRenderableObject->GetMeshCount(); meshIndex++)
  {
    m_pRenderableObject->BindMesh(meshIndex);
    m_pRenderableObject->Render(parentWorldMatrix * GetWorldMatrix(), viewMatrix, projectionMatrix, animationTime, m_activeAnimation);
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