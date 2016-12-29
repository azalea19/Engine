#ifndef MCamera_H__
#define MCamera_H__

#include "Types.h"
#include "AffineTransformable.h"

/**
* @file   MCamera.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The camera class.
*
* The camera class handles the calculation of the camera directions.
*
* All of the camera class functions such as Forward() etc, return world space direction vectors
*
* In dealing with the view matrix, and the calculation of the worldspace direction vectors
* I found the following diagrammatic representation of the 3d transformation pipeline extremely helpful:
* https://capnramses.github.io//opengl/raycasting.html
*/


class MCamera : public AffineTransformable
{
	mat4 projectionMatrix;	///< the projection matrix

public:
	/**
	* @brief default constructor
	*/
	MCamera();

	MCamera(float fov, int screenwidth, int screenheight, float nearplane, float farplane);


	/**
	* @brief Calculates the forward vector of the camera
	*
	* @return vec3
	*/
	vec3 Forward() const;

	/**
	* @brief Calculates the backward vector of the camera
	*
	* @return vec3
	*/
	vec3 Backward() const;

	/**
	* @brief Calculates the up vector of the camera
	*
	* @return vec3
	*/
	vec3 Up() const;

	/**
	* @brief Calculates the down vector of the camera
	*
	* @return vec3
	*/
	vec3 Down() const;

	/**
	* @brief Calculates the left vector of the camera
	*
	* @return vec3
	*/
	vec3 Left() const;

	/**
	* @brief Calculates the right vector of the camera
	*
	* @return vec3
	*/
	vec3 Right() const;

	/**
	* @brief Set the position of the camera
	*
	* @return void
	*/
	void SetPosition(vec3 pos);

	/**
	* @brief Get the position of the camera
	*
	* @return vec3
	*/
	vec3 GetPosition() const;

	/**
	* @brief Gets the forward direction of the camera, but disregard changes in the pitch of the camera
	* This allows the player to look up while still moving forward instead of up and forward.
	*
	* @return vec3
	*/
	vec3 ForwardNoPitch() const;

	/**
	* @brief Get the projection matrix of the camera
	*
	* @return mat4
	*/
	mat4 getProjectionMatrix() const;

	/**
	* @brief Gets the backwards direction of the camera, but disregard changes in the pitch of the camera
	*
	* @return vec3

	*/
	vec3 BackwardNoPitch() const;
	

	/**
	* @brief Get the view matrix
	*
	* @return mat4
	*/
	mat4 getViewMatrix() const;


  /**
  * @brief Set the near plane and far plane
  *
  * @return void
  */
  void SetClipPlanes(float near, float far);

};

#endif