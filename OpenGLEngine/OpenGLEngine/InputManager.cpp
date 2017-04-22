#include "InputManager.h"
#include "SDL.h"



void InputManager::Initialise(IInputHandler* inputHandler)
{
  input = std::unique_ptr<IInputHandler>(inputHandler);
}

void InputManager::Update()
{
  input->Update();
}


bool InputManager::IsKeyDown(int keyCode) const
{
  return input->IsKeyDown(keyCode);
}

bool InputManager::IsKeyUp(int keyCode) const
{
  return input->IsKeyUp(keyCode);
}

bool InputManager::IsKeyPressed(int keyCode) const
{
  return input->IsKeyPressed(keyCode);
}

bool InputManager::IsKeyReleased(int keyCode) const
{
  return input->IsKeyReleased(keyCode);
}

bool InputManager::IsMouseDownLeft() const
{
  return input->IsMouseDownLeft();
}

bool InputManager::IsMouseUpLeft() const
{
  return input->IsMouseUpLeft();
}

bool InputManager::IsMousePressedLeft() const
{
  return input->IsMousePressedLeft();
}

bool InputManager::IsMouseReleasedLeft() const
{
  return input->IsMouseReleasedLeft();
}

bool InputManager::IsMouseDownRight() const
{
  return input->IsMouseDownRight();
}

bool InputManager::IsMouseUpRight() const
{
  return input->IsMouseUpRight();
}

bool InputManager::IsMousePressedRight() const
{
  return input->IsMousePressedRight();
}

bool InputManager::IsMouseReleasedRight() const
{
  return input->IsMouseReleasedRight();
}

int32_t InputManager::MouseDeltaX() const
{
  return input->MouseDeltaX();
}

int32_t InputManager::MouseDeltaY() const
{
  return input->MouseDeltaY();
}

uint8_t InputManager::KeyboardState(int keyCode) const
{
  return input->KeyboardState(keyCode);
}

uint8_t InputManager::LastKeyboardState(int keyCode) const
{
  return input->LastKeyboardState(keyCode);
}