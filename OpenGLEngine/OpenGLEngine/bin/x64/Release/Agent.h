#ifndef Agent_h__
#define Agent_h__

#include "MMath.h"
#include "Types.h"
//#include "AABoundingBox.h"


/**
* @file   Agent.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The agent class.
*
* The base agent class used by other more specific agents to inherit from.
*/

//These are binary values so they can be anded or or'd together, 
//This will allow an agent to be more than one of the properties without a long list of ifs and bools
enum AgentProperty : uint32_t
{
	AP_collidable = 1,
	AP_climbable = 2,
	AP_interactable = 4,
	AP_colourRed = 8,
	AP_colourBlue = 16,
	AP_colourYellow = 32,
	AP_colourPurple = 64,
	AP_moving = 128

	//AP_collidable = 0b00000001,
	//AP_climbable = 0b00000010,
	//AP_interactable = 0b00000100,

};


struct Agent
{

public:

	/**
	* @brief Calls the supplied update function if it has been implemented
	*
	* @return void
	*/
	virtual void Update() = 0;

	/**
	* @brief Returns the number of sub-objects in the model rendered with a different material
	*
	* @return int
	*/
	virtual int SubObjectCount() = 0;

	/**
	* @brief Returns a vector of vertices for the specified sub object
	*
	* @param subIndex - the index of the sub object needed
	* @param parentModelMatrix - the parent model matrix
	*
	* @return std::vector<glm::vec3>
	*/
	virtual std::vector<glm::vec3> GetVertices(int subIndex, glm::mat4 parentModelMatrix = glm::mat4()) = 0;

	/**
	* @brief Returns the climbability of the sub-object
	*
	* @param subIndex - the index of the sub-object needed
	*
	* @return bool
	*/

	virtual bool IsClimbable(int subIndex) = 0;

	/**
	* @brief Render an object
	*
	* @param viewMatrix - the viewMatrix
	* @param projectionMatrix - the projection matrix
	* @param parentModelMatrix - the parent model matrix
	*
	* @return void
	*/

	virtual void Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 parentModelMatrix = glm::mat4()) = 0;

	/**
	* @brief Sets the position that the model will be rendered at in the world
	*
	* @param coords - the new coordinates
	*
	* @return void
	*/


	void SetPosition(glm::vec3 coords);

	/**
	* @brief Get the posistion of the agent
	*
	* @return vec3
	*/

	vec3 GetPosition();

	/**
	* @brief Sets the scale that the model will be rendered at in the world
	*
	* @param a_scale - the new scale
	*
	* @return void
	*/

	void SetScale(glm::vec3 a_scale);

	/**
	* @brief Rotates the model by a specified number of degrees around the x-axis
	*
	* @param degrees - the new value for pitch in degrees
	*
	* @return void
	*/

	void SetPitch(float degrees);


  /**
  * @brief Gets the pitch
  *
  * @return float
  */
	float GetPitch();


	/**
	* @brief Rotates the model by a specified number of degrees around the y-axis
	*
	* @param degrees - the new value for yaw in degrees
	*
	* @return void
	*/
	void SetYaw(float degrees);

  /**
  * @brief Gets the yaw
  *
  * @return float
  */
	float GetYaw();

	/**
	* @brief Determines whether or not the object is visible.
	*
	* @param b - bool to set whether or not visible. True for visible, false for invisible.
	*
	* @return void
	*/
	void SetVisible(bool b) { m_visible = b; }

	/**
	* @brief Returns true if the object is visible, false if the object is invisible.
	*
	* @return bool
	*/
	bool GetVisible() { return m_visible; }

	/**
	* @brief Gets the model matrix
	*
	* @return glm::mat4
	*/

	glm::mat4 GetModelMatrix();

	/**
	* @brief Get the value (true/false) of a specified AgentProperty.
	*
	* @param target - Name of the agent property to check.
	*
	* @return void
	*/

	bool CheckProperty(AgentProperty target);

	/**
	* @brief Set the value (true/false) of a specified AgentProperty.
	*
	* @param prop - Name of the AgentProperty to set.
	* @param value - Bool to set the AgentProperty to.
	*
	* @return void
	*/
	void SetProperty(AgentProperty prop, bool value);

	/**
	* @brief set the value for disabled
	*
	* @param newDis - the new value for disabled
	*
	* @return void
	*/

	void SetDisabled(bool newDis);

	/**
	* @brief Get the value for disabled
	*
	* @return bool
	*/

	bool GetDisabled();

protected:

	bool m_disabled = false;	///< disabled - whether the agent is disabled
	glm::vec3 m_position;		///< posistion - the coordinates of the agent
	glm::vec3 m_scale;		///< scale - the scale of the agent
	float m_yaw = 0;				///< yaw - the yaw of the agent
	float m_pitch = 0;			///< pitch - the pitch of the agent
	bool m_visible = true;		///< visible - whether the agent is visible
	AgentProperty m_properties;	///< properties - properties of the agent
};

#endif 