/**
A virtual class for a scene with functions to initialise, Render and update, and a bool for when it has finished.

CHANGE LOG:
- Written & commented - Maddy Topaz
- 25/10/16 Comments for initialise() and top of file - Elizabeth Haynes
*/

/**
* @file   Scene.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The scene class.
*
* The scene class is used as the base class for games scenes to inherit from.
*/

#ifndef Scene_h__
#define Scene_h__

#include <vector>
#include "Agent.h"
//#include "Object.h"

class Scene
{

public:

	/**
	* @brief Initialises the scene. Should run when scene begins.
	*/
	virtual void Initialise() = 0;

	/**
	* @brief Should return true when the scene has been completed.
	*/
	virtual bool Finished() = 0;

	/**
	* @brief perform an update to the scene
	*
	* @return void
	*/
	virtual void Update() = 0;

	/**
	* @brief Render the scene
	*
	* @return void
	*/
	virtual void Render() = 0;

	string GetName() { return m_name; }
	void SetName(string nam) { m_name = nam; }

private:
	string m_name = "";
};

#endif