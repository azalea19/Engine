#include "ObjectInstance.h"
#include "ShaderLibrary.h"

void ObjectInstance::Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 parentModelMatrix /*= glm::mat4()*/)
{
	m_renderableObject->Render(viewMatrix, projectionMatrix, parentModelMatrix * GetModelMatrix());
}

glm::mat4 ObjectInstance::GetModelMatrix()
{
  glm::mat4 scaleMatrix = glm::scale(scale);
  glm::mat4 YrotationMatrix = glm::rotate(((yaw)* 3.1416f / 180), glm::vec3(0, 1, 0));
  glm::mat4 XrotationMatrix = glm::rotate(((pitch)* 3.1416f / 180), glm::vec3(1, 0, 0));
  glm::mat4 translationMatrix = glm::translate(position);

  //rotates and THEN translates
  return translationMatrix * XrotationMatrix * YrotationMatrix * scaleMatrix;
}

std::vector<glm::vec3> ObjectInstance::GetVertices(int subIndex, glm::mat4 parentModelMatrix /*= glm::mat4()*/)
{
  std::vector<glm::vec3> verts;
  verts = m_renderableObject->GetVertices(subIndex);
  glm::mat4 modelMatrix = parentModelMatrix * GetModelMatrix();

  glm::vec4 temp;
  for (uint32_t i = 0; i < verts.size(); i++)
  {
    temp = glm::vec4(verts[i], 1);
    temp = modelMatrix * temp;
    verts[i].x = temp.x;
    verts[i].y = temp.y;
    verts[i].z = temp.z;
  }

  return verts;
}

int ObjectInstance::SubObjectCount()
{
  return m_renderableObject->SubObjectCount();
}

void ObjectInstance::SetYaw(float degrees)
{
  yaw = degrees;
}

void ObjectInstance::SetPitch(float degrees)
{
  pitch = degrees;
}

void ObjectInstance::SetScale(glm::vec3 a_scale)
{
  scale = a_scale;
}

void ObjectInstance::SetPosition(glm::vec3 coords)
{
  position = coords;
}

ObjectInstance::ObjectInstance(RenderableObject* object, glm::vec3 coords, glm::vec3 scaleFactor, float a_yaw, float a_pitch)
{
	m_renderableObject = object;
	position = coords;
	scale = scaleFactor;
	yaw = a_yaw;
	pitch = a_pitch;
}

bool ObjectInstance::IsClimbable(int subIndex)
{
	return m_renderableObject->IsClimbable(subIndex);
}

const RenderableObject & ObjectInstance::GetRenderableObject() const
{
	return *m_renderableObject;
}

glm::vec3 ObjectInstance::GetPosition() const
{
	return position;
}

glm::vec3 ObjectInstance::GetScale() const
{
	return scale;
}

float ObjectInstance::GetYaw() const
{
	return yaw;

}

float ObjectInstance::GetPitch() const
{
	return pitch;
}