#ifndef MPlayer_h__
#define MPlayer_h__

/**
Class for a player that has a location, and 'look' ray.

CHANGE LOG
- Class created. Ray (and location?) added. - Maddie Topaz
- Class created. Inventory and location added. - Elizabeth Haynes
- Merged Maddie & Liz versions of this class - Elizabeth Haynes
- Header file commenting - Elizabeth Haynes, Maddie Topaz
- Seperated to MPlayer with MCamera member - Maddy
*/

/**
* @file   MPlayer.h
* @Author Maddisen Topaz, Liz Haynes
* @date   S2, 2016
* @brief  The player class.
*
* The player class used in scenes.
*/

#pragma once

#include "Types.h"
#include "GeometricPrimitives.h"

class MCamera;

class MPlayer
{

protected:
	MCamera* camera;	///< the players camera
	float height = 150;	///< the players height

public:
	/**
	* @brief Default constructor for MPlayer.
	*/
	MPlayer();
	/**
	* @brief Get the player camera.
	*/
	MCamera* GetCamera() const;

	/**
	* @brief Returns vec3 of the player's position
	*
	* @return vec3
	*/
	vec3 GetPosition() const;

	/**
	* @brief Sets player's position
	*
	* @param position - the position of the camera
	*
	* @return void
	*/
	void SetPosition(vec3 const& position);

	/**
	* @brief Get's the player's Ray.
	*
	* @return mRay
	*/
	mRay GetPickingRay() const;

	/**
	* @brief Get height of camera.
	*
	* @return float
	*/
	float GetHeight() const;

	/**
	* @brief Set height of camera.
	*
	* @param Height - the height of the camera
	*
	* @return void
	*/
	void SetHeight(float Height);
};

#endif

