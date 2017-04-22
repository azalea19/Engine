#include "GLInputHandler.h"
#include "SDL.h"


GLInputHandler::GLInputHandler()
{
  memset(lastKeyboardState, 0, 16384);
  memset(keyboardState, 0, 16384);
  Update();
}

bool GLInputHandler::HandleEvents()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_QUIT:
        return false;
      case SDL_MOUSEMOTION:
        PushEvent(MouseEvent(event.motion));
        break;
      case SDL_MOUSEBUTTONDOWN:
        PushEvent(MouseEvent(event.button));
        break;
      case SDL_MOUSEBUTTONUP:
        PushEvent(MouseEvent(event.button));
        break;
    }
  }
  return true;
}

void GLInputHandler::ProcessButtonEvent(SDL_MouseButtonEvent _event)
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

void GLInputHandler::ProcessMotionEvent(SDL_MouseMotionEvent _event)
{
  mouseDeltaX = _event.xrel;
  mouseDeltaY = _event.yrel;
}

void GLInputHandler::ProcessEventQueue()
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

void GLInputHandler::Update()
{
  HandleEvents();

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

void GLInputHandler::PushEvent(MouseEvent const & _event)
{
  m_eventQueue.push_back(_event);
}

bool GLInputHandler::IsKeyDown(int keyCode) const
{
  return keyboardState[keyCode] != 0;
}

bool GLInputHandler::IsKeyUp(int keyCode) const
{
  return !IsKeyDown(keyCode);
}

bool GLInputHandler::IsKeyPressed(int keyCode) const
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

bool GLInputHandler::IsKeyReleased(int keyCode) const
{
  return IsKeyUp(keyCode) && (lastKeyboardState[keyCode] != 0);
}

bool GLInputHandler::IsMouseDownLeft() const
{
  return mouseButtonStates[SDL_BUTTON_LEFT].down;
}

bool GLInputHandler::IsMouseUpLeft() const
{
  return !IsMouseDownLeft();
}

bool GLInputHandler::IsMousePressedLeft() const
{
  return mouseButtonStates[SDL_BUTTON_LEFT].pressed;
}

bool GLInputHandler::IsMouseReleasedLeft() const
{
  return mouseButtonStates[SDL_BUTTON_LEFT].released;
}

bool GLInputHandler::IsMouseDownRight() const
{
  return mouseButtonStates[SDL_BUTTON_RIGHT].down;
}

bool GLInputHandler::IsMouseUpRight() const
{
  return !IsMouseDownRight();
}

bool GLInputHandler::IsMousePressedRight() const
{
  return mouseButtonStates[SDL_BUTTON_RIGHT].pressed;
}

bool GLInputHandler::IsMouseReleasedRight() const
{
  return mouseButtonStates[SDL_BUTTON_RIGHT].released;
}

int32_t GLInputHandler::MouseDeltaX() const
{
  return mouseDeltaX;
}

int32_t GLInputHandler::MouseDeltaY() const
{
  return mouseDeltaY;
}

uint8_t GLInputHandler::KeyboardState(int keyCode) const
{
  return keyboardState[keyCode];
}

uint8_t GLInputHandler::LastKeyboardState(int keyCode) const
{
  return lastKeyboardState[keyCode];
}