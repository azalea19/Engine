#ifndef ObjectInstance_h__
#define ObjectInstance_h__

#include "RenderableObject.h"

/**
* @file   ObjectInstance.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The object instance struct.
*
* The object instance class stores the data relating to a particular instance of a model.
*/


struct ObjectInstance
{

	
	ObjectInstance(RenderableObject* object, glm::vec3 coords = glm::vec3(0, 0, 0), glm::vec3 scaleFactor = glm::vec3(1, 1, 1), float a_yaw = 0, float a_pitch = 0);

	

	void SetPosition(glm::vec3 coords);

	
	void SetScale(glm::vec3 a_scale);

	
	void SetPitch(float degrees);

	

	void SetYaw(float degrees);

	
	int SubObjectCount();

	
	std::vector<glm::vec3> GetVertices(int subIndex, glm::mat4 parentModelMatrix = glm::mat4());



	bool IsClimbable(int subIndex);


	glm::mat4 GetModelMatrix();



	void Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 parentModelMatrix = glm::mat4());



	const RenderableObject & GetRenderableObject() const;



	glm::vec3 GetPosition() const;



	glm::vec3 GetScale() const;


	float GetYaw() const;


	float GetPitch() const;

	

private:

	RenderableObject * m_renderableObject;		
	glm::vec3 position;				
	glm::vec3 scale;				
	float yaw = 0;					
	float pitch = 0;				
};

#endif //ObjectInstance_h__