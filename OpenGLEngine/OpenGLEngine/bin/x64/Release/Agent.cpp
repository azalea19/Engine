#include "Agent.h"
#include "MMath.h"

glm::mat4 Agent::GetModelMatrix()
{
  glm::mat4 scaleMatrix = glm::scale(m_scale);
  glm::mat4 YrotationMatrix = glm::rotate(((m_yaw)* 3.1416f / 180), glm::vec3(0, 1, 0));
  glm::mat4 XrotationMatrix = glm::rotate(((m_pitch)* 3.1416f / 180), glm::vec3(1, 0, 0));
  glm::mat4 translationMatrix = glm::translate(m_position);

  //rotates and THEN translates
  return translationMatrix * XrotationMatrix * YrotationMatrix * scaleMatrix;
}

void Agent::SetYaw(float degrees)
{
  m_yaw = degrees;
}

float Agent::GetYaw()
{
  return m_yaw;
}

void Agent::SetPitch(float degrees)
{
  m_pitch = degrees;
}

float Agent::GetPitch()
{
  return m_pitch;
}

void Agent::SetScale(glm::vec3 a_scale)
{
  m_scale = a_scale;
}

void Agent::SetPosition(glm::vec3 coords)
{
  m_position = coords;
}

vec3 Agent::GetPosition()
{
	return m_position;
}

///Returns climbability of subObject
bool Agent::IsClimbable(int subIndex)
{
	return false;
}


bool Agent::CheckProperty(AgentProperty target)
{
	return (m_properties & target) != 0;
}


void Agent::SetProperty(AgentProperty prop, bool value)
{
	if (value)
	{
		m_properties = (AgentProperty)(m_properties | prop);
	}
	else
	{
		m_properties = (AgentProperty)(m_properties & ~prop);
	}
}

void Agent::SetDisabled(bool newDis) {
	m_disabled = newDis;
}

bool Agent::GetDisabled() {
	return m_disabled;
}