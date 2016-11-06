#ifndef InputManager_H__
#define InputManager_H__
#include <cstdint>
#include "SDL.h"
#include "Types.h"

/**
* @file   InputManager.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The input manager.
*
* The input manager uses the SDL2 library to create an event queue of mouse button and mouse motion events
* See SDL_MouseButtonEvent or SDL_MouseMotionEvent: 
* https://wiki.libsdl.org/SDL_MouseButtonEvent
* https://wiki.libsdl.org/SDL_MouseMotionEvent
* The state of the keyboard is kept track of so that the input manager may be queried about if a key has been pressed, 
* released or is down.
* 
*/


enum MouseEventType : uint32_t
{
	ME_BUTTON = 0,
	ME_MOTION = 1,
};


union SDL_MOUSE_EVENT
{
	SDL_MouseButtonEvent buttonEvent;
	SDL_MouseMotionEvent motionEvent;
};


struct MouseEvent
{
	MouseEventType eventType;
	SDL_MOUSE_EVENT mouseEvent;

	MouseEvent(SDL_MouseButtonEvent _event)
	{
		eventType = ME_BUTTON;
		mouseEvent.buttonEvent = _event;
	}

	MouseEvent(SDL_MouseMotionEvent _event)
	{
		eventType = ME_MOTION;
		mouseEvent.motionEvent = _event;
	}
};

struct MouseButtonState
{
	bool pressed;
	bool released;
	bool down;
};

class InputManager
{
	std::vector<MouseEvent> eventQueue;
	int keyStateSize = 0;

	void ProcessButtonEvent(SDL_MouseButtonEvent _event);
	void ProcessMotionEvent(SDL_MouseMotionEvent _event);
	void ProcessEventQueue();

public:

	InputManager();

	static InputManager* GetInputManager();

	uint8_t keyboardState[16384];
	uint8_t lastKeyboardState[16384];

	MouseButtonState mouseButtonStates[4];

	int32_t mouseDeltaX;
	int32_t mouseDeltaY;

	
	void Update();

	
	void PushEvent(MouseEvent const& _event);


	bool IsKeyDown(int keyCode);


	
	bool IsKeyUp(int keyCode);

	
	bool IsKeyPressed(int keyCode); 
	

	bool IsKeyReleased(int keyCode); 
	

	bool IsMouseDownLeft();

	
	bool IsMouseUpLeft();

	
	bool IsMousePressedLeft();

	
	bool IsMouseReleasedLeft();

	
	bool IsMouseDownRight();

	
	bool IsMouseUpRight();

	
	bool IsMousePressedRight();

	
	bool IsMouseReleasedRight();


	int32_t MouseDeltaX();


	int32_t MouseDeltaY();

};
#endif
