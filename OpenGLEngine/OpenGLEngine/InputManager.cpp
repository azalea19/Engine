#include "InputManager.h"
#include "SDL.h"

static InputManager singleton;

InputManager::InputManager()
{
	memset(lastKeyboardState, 0, 16384);
	memset(keyboardState, 0, 16384);
	Update();
}

void InputManager::ProcessButtonEvent(SDL_MouseButtonEvent _event)
{
	MouseButtonState& buttonState = mouseButtonStates[_event.button];
	switch (_event.state)
	{
		case SDL_PRESSED:
			buttonState.pressed = true;
			buttonState.down = true;
			break;
		case SDL_RELEASED:
			buttonState.released = true;
			buttonState.down = false;
	}
}

void InputManager::ProcessMotionEvent(SDL_MouseMotionEvent _event)
{
	mouseDeltaX = _event.xrel;
	mouseDeltaY = _event.yrel;
}

void InputManager::ProcessEventQueue()
{
	mouseDeltaX = 0;
	mouseDeltaY = 0;
	for (int i = 0; i < 4; i++)
	{
		mouseButtonStates[i].pressed = false;
		mouseButtonStates[i].released = false;
	}
	for (size_t i = 0; i < eventQueue.size(); i++)
	{
		MouseEvent& nextEvent = eventQueue[i];
		switch (nextEvent.eventType)
		{
			case ME_BUTTON:
				ProcessButtonEvent(nextEvent.mouseEvent.buttonEvent);
				break;
			case ME_MOTION:
				ProcessMotionEvent(nextEvent.mouseEvent.motionEvent);
		}
	}
	eventQueue.clear();
}

InputManager *InputManager::GetInputManager()
{
	return &singleton;
}

void InputManager::Update()
{
	static int counter = 0;
	ProcessEventQueue();

	SDL_PumpEvents();
	memset(lastKeyboardState, 0, 16384);
	for (int i = 0; i < keyStateSize; i++)
	{
		if (keyboardState[i] != 0)
		{
			break;
		}
	}
	memcpy(lastKeyboardState, keyboardState, keyStateSize);
	const uint8_t* temp = SDL_GetKeyboardState(&keyStateSize);
	memcpy(keyboardState, temp, keyStateSize);
}

void InputManager::PushEvent(MouseEvent const & _event)
{
	eventQueue.push_back(_event);
}

bool InputManager::IsKeyDown(int keyCode)
{
	return keyboardState[keyCode] != 0;
}

bool InputManager::IsKeyUp(int keyCode)
{
	return !IsKeyDown(keyCode);
}

bool InputManager::IsKeyPressed(int keyCode)
{
	if (IsKeyDown(keyCode))
	{
		if (lastKeyboardState[keyCode] == 0)
		{
			return true;
		}
	}
	return false;

}

bool InputManager::IsKeyReleased(int keyCode)
{
	return IsKeyUp(keyCode) && (lastKeyboardState[keyCode] != 0);
}

bool InputManager::IsMouseDownLeft()
{
	return mouseButtonStates[SDL_BUTTON_LEFT].down;
}

bool InputManager::IsMouseUpLeft()
{
	return !IsMouseDownLeft();
}

bool InputManager::IsMousePressedLeft()
{
	return mouseButtonStates[SDL_BUTTON_LEFT].pressed;
}

bool InputManager::IsMouseReleasedLeft()
{
	return mouseButtonStates[SDL_BUTTON_LEFT].released;
}

bool InputManager::IsMouseDownRight()
{
	return mouseButtonStates[SDL_BUTTON_RIGHT].down;
}

bool InputManager::IsMouseUpRight()
{
	return !IsMouseDownRight();
}

bool InputManager::IsMousePressedRight()
{
	return mouseButtonStates[SDL_BUTTON_RIGHT].pressed;
}

bool InputManager::IsMouseReleasedRight()
{
	return mouseButtonStates[SDL_BUTTON_RIGHT].released;
}

int32_t InputManager::MouseDeltaX()
{
	return mouseDeltaX;
}

int32_t InputManager::MouseDeltaY()
{
	return mouseDeltaY;
}
