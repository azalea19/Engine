#ifndef ExampleScene_h__
#define ExampleScene_h__

#include "Scene.h"

struct RigidBody;
class MPlayer;

/**
* @file   ExampleScene.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  An example scene.
*
* The example scene does not appear in the game. Written as a reference for functionality of the engine.
* Shows how to call and use various methods, managers and libraries.
*/


class ExampleScene : public Scene
{


public:

	ExampleScene();

	virtual void Initialise() override;

	//Should return true when the room puzzle has been completed.
	virtual bool Finished() override;

	/**
	* @brief perform an update to the scene
	*
	* @param position - the position of the object
	*
	* @return int
	*/
	virtual void Update() override;

	/**
	* @brief Render the scene
	*
	* @param viewMatrix - the view matrix
	* @param projectionMatrix - the projection matrix
	*
	* @return void
	*/
	virtual void Render() override;

private:

	void UpdatePlayer();

	MPlayer *player;
	RigidBody *room;
	RigidBody *lilRabbit;
	RigidBody *finishPlatform;
};

#endif HallScene_h__

