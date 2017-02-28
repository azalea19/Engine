#include "InputManager.h"
#include "SDL.h"


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
	for (size_t i = 0; i < m_eventQueue.size(); i++)
	{
		MouseEvent& nextEvent = m_eventQueue[i];
		switch (nextEvent.eventType)
		{
			case ME_BUTTON:
				ProcessButtonEvent(nextEvent.mouseEvent.buttonEvent);
				break;
			case ME_MOTION:
				ProcessMotionEvent(nextEvent.mouseEvent.motionEvent);
		}
	}
	m_eventQueue.clear();
}

void InputManager::Update()
{
	static int counter = 0;
	ProcessEventQueue();

	SDL_PumpEvents();
	memset(lastKeyboardState, 0, 16384);
	for (int i = 0; i < m_keyStateSize; i++)
	{
		if (keyboardState[i] != 0)
		{
			break;
		}
	}
	memcpy(lastKeyboardState, keyboardState, m_keyStateSize);
	const uint8_t* temp = SDL_GetKeyboardState(&m_keyStateSize);
	memcpy(keyboardState, temp, m_keyStateSize);
}

void InputManager::PushEvent(MouseEvent const & _event)
{
	m_eventQueue.push_back(_event);
}

bool InputManager::IsKeyDown(int keyCode) const
{
	return keyboardState[keyCode] != 0;
}

bool InputManager::IsKeyUp(int keyCode) const
{
	return !IsKeyDown(keyCode);
}

bool InputManager::IsKeyPressed(int keyCode) const
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

bool InputManager::IsKeyReleased(int keyCode) const
{
	return IsKeyUp(keyCode) && (lastKeyboardState[keyCode] != 0);
}

bool InputManager::IsMouseDownLeft() const
{
	return mouseButtonStates[SDL_BUTTON_LEFT].down;
}

bool InputManager::IsMouseUpLeft() const
{
	return !IsMouseDownLeft();
}

bool InputManager::IsMousePressedLeft() const
{
	return mouseButtonStates[SDL_BUTTON_LEFT].pressed;
}

bool InputManager::IsMouseReleasedLeft() const
{
	return mouseButtonStates[SDL_BUTTON_LEFT].released;
}

bool InputManager::IsMouseDownRight() const
{
	return mouseButtonStates[SDL_BUTTON_RIGHT].down;
}

bool InputManager::IsMouseUpRight() const
{
	return !IsMouseDownRight();
}

bool InputManager::IsMousePressedRight() const
{
	return mouseButtonStates[SDL_BUTTON_RIGHT].pressed;
}

bool InputManager::IsMouseReleasedRight() const
{
	return mouseButtonStates[SDL_BUTTON_RIGHT].released;
}

int32_t InputManager::MouseDeltaX() const
{
	return mouseDeltaX;
}

int32_t InputManager::MouseDeltaY() const
{
	return mouseDeltaY;
}
