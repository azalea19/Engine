#ifndef GLInputHandler_h__
#define GLInputHandler_h__

#include <cstdint>
#include "SDL.h"
#include "Types.h"
#include "IInputHandler.h"
#include <memory>

/**
* @file   GLInputHandler.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief  The input manager.
*
* The GL input handler uses the SDL2 library to create an event queue of mouse button and mouse motion events
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

class GLInputHandler : public IInputHandler
{

public:

  GLInputHandler();

  /// <summary>
  /// Updates this instance.
  /// </summary>
  virtual void Update() override;

  /// <summary>
  /// Determines whether [is key down] [the specified key code].
  /// </summary>
  /// <param name="keyCode">The key code.</param>
  /// <returns>
  ///   <c>true</c> if [is key down] [the specified key code]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsKeyDown(int keyCode) const override;



  /// <summary>
  /// Determines whether [is key up] [the specified key code].
  /// </summary>
  /// <param name="keyCode">The key code.</param>
  /// <returns>
  ///   <c>true</c> if [is key up] [the specified key code]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsKeyUp(int keyCode) const override;


  /// <summary>
  /// Determines whether [is key pressed] [the specified key code].
  /// </summary>
  /// <param name="keyCode">The key code.</param>
  /// <returns>
  ///   <c>true</c> if [is key pressed] [the specified key code]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsKeyPressed(int keyCode) const override;


  /// <summary>
  /// Determines whether [is key released] [the specified key code].
  /// </summary>
  /// <param name="keyCode">The key code.</param>
  /// <returns>
  ///   <c>true</c> if [is key released] [the specified key code]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsKeyReleased(int keyCode) const override;


  /// <summary>
  /// Determines whether [is mouse down left].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse down left]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsMouseDownLeft() const override;


  /// <summary>
  /// Determines whether [is mouse up left].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse up left]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsMouseUpLeft() const override;


  /// <summary>
  /// Determines whether [is mouse pressed left].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse pressed left]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsMousePressedLeft() const override;


  /// <summary>
  /// Determines whether [is mouse released left].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse released left]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsMouseReleasedLeft() const override;


  /// <summary>
  /// Determines whether [is mouse down right].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse down right]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsMouseDownRight() const override;


  /// <summary>
  /// Determines whether [is mouse up right].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse up right]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsMouseUpRight() const override;


  /// <summary>
  /// Determines whether [is mouse pressed right].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse pressed right]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsMousePressedRight() const override;


  /// <summary>
  /// Determines whether [is mouse released right].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse released right]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsMouseReleasedRight() const override;


  /// <summary>
  /// Gets the change in x.
  /// </summary>
  /// <returns>int32_t</returns>
  virtual int32_t MouseDeltaX() const override;


  /// <summary>
  /// Gets the change in y.
  /// </summary>
  /// <returns>int32_t</returns>
  virtual int32_t MouseDeltaY() const override;

  /// <summary>
  /// Current keyboard state.
  /// </summary>
  /// <param name="keyCode">The key code.</param>
  /// <returns></returns>
  virtual uint8_t KeyboardState(int keyCode) const override;


  /// <summary>
  /// Last keyboard state.
  /// </summary>
  /// <param name="keyCode">The key code.</param>
  /// <returns></returns>
  virtual uint8_t LastKeyboardState(int keyCode) const override;

private:

  /// <summary>
  /// The event queue
  /// </summary>
  std::vector<MouseEvent> m_eventQueue;

  /// <summary>
  /// The key state size
  /// </summary>
  int m_keyStateSize = 0;


  /// <summary>
  /// Processes the button event.
  /// </summary>
  /// <param name="_event">The event.</param>
  void ProcessButtonEvent(SDL_MouseButtonEvent _event);

  /// <summary>
  /// Processes the motion event.
  /// </summary>
  /// <param name="_event">The event.</param>
  void ProcessMotionEvent(SDL_MouseMotionEvent _event);

  /// <summary>
  /// Processes the event queue.
  /// </summary>
  void ProcessEventQueue();

  /// <summary>
  /// Pushes the event.
  /// </summary>
  /// <param name="_event">The event.</param>
  void PushEvent(MouseEvent const& _event);

  /// <summary>
  /// Handles the events.
  /// </summary>
  /// <returns></returns>
  bool HandleEvents();

  /// <summary>
  /// The keyboard state
  /// </summary>
  uint8_t keyboardState[16384];

  /// <summary>
  /// The last keyboard state
  /// </summary>
  uint8_t lastKeyboardState[16384];

  /// <summary>
  /// The mouse button states
  /// </summary>
  MouseButtonState mouseButtonStates[4];

  /// <summary>
  /// The mouse delta x
  /// </summary>
  int32_t mouseDeltaX;

  /// <summary>
  /// The mouse delta y
  /// </summary>
  int32_t mouseDeltaY;


};


#endif // GLInputHandler_h__
