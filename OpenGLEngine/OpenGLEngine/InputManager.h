 #ifndef InputManager_H__
#define InputManager_H__
#include <cstdint>
#include "SDL.h"
#include "Types.h"
#include "IInputHandler.h"
#include "Singleton.h"
#include <memory>

/**
* @file   InputManager.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief  The input manager.
*
* 
* A wrapper to access input handler functions through an API independent Input Handler.
*/



class InputManager : public Singleton<InputManager>
{

public:

  void Initialise(IInputHandler* inputHandler);

  /// <summary>
  /// Updates this instance.
  /// </summary>
  void Update();

  /// <summary>
  /// Determines whether [is key down] [the specified key code].
  /// </summary>
  /// <param name="keyCode">The key code.</param>
  /// <returns>
  ///   <c>true</c> if [is key down] [the specified key code]; otherwise, <c>false</c>.
  /// </returns>
  bool IsKeyDown(int keyCode) const;


	
  /// <summary>
  /// Determines whether [is key up] [the specified key code].
  /// </summary>
  /// <param name="keyCode">The key code.</param>
  /// <returns>
  ///   <c>true</c> if [is key up] [the specified key code]; otherwise, <c>false</c>.
  /// </returns>
  bool IsKeyUp(int keyCode) const;

	
  /// <summary>
  /// Determines whether [is key pressed] [the specified key code].
  /// </summary>
  /// <param name="keyCode">The key code.</param>
  /// <returns>
  ///   <c>true</c> if [is key pressed] [the specified key code]; otherwise, <c>false</c>.
  /// </returns>
  bool IsKeyPressed(int keyCode) const;
	

  /// <summary>
  /// Determines whether [is key released] [the specified key code].
  /// </summary>
  /// <param name="keyCode">The key code.</param>
  /// <returns>
  ///   <c>true</c> if [is key released] [the specified key code]; otherwise, <c>false</c>.
  /// </returns>
  bool IsKeyReleased(int keyCode) const;
	

  /// <summary>
  /// Determines whether [is mouse down left].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse down left]; otherwise, <c>false</c>.
  /// </returns>
  bool IsMouseDownLeft() const;

	
  /// <summary>
  /// Determines whether [is mouse up left].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse up left]; otherwise, <c>false</c>.
  /// </returns>
  bool IsMouseUpLeft() const;

	
  /// <summary>
  /// Determines whether [is mouse pressed left].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse pressed left]; otherwise, <c>false</c>.
  /// </returns>
  bool IsMousePressedLeft() const;

	
  /// <summary>
  /// Determines whether [is mouse released left].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse released left]; otherwise, <c>false</c>.
  /// </returns>
  bool IsMouseReleasedLeft() const;

	
  /// <summary>
  /// Determines whether [is mouse down right].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse down right]; otherwise, <c>false</c>.
  /// </returns>
  bool IsMouseDownRight() const;

	
  /// <summary>
  /// Determines whether [is mouse up right].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse up right]; otherwise, <c>false</c>.
  /// </returns>
  bool IsMouseUpRight() const;

	
  /// <summary>
  /// Determines whether [is mouse pressed right].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse pressed right]; otherwise, <c>false</c>.
  /// </returns>
  bool IsMousePressedRight() const;

	
  /// <summary>
  /// Determines whether [is mouse released right].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse released right]; otherwise, <c>false</c>.
  /// </returns>
  bool IsMouseReleasedRight() const;


  /// <summary>
  /// Gets the change in x.
  /// </summary>
  /// <returns>int32_t</returns>
  int32_t MouseDeltaX() const;


  /// <summary>
  /// Gets the change in y.
  /// </summary>
  /// <returns>int32_t</returns>
  int32_t MouseDeltaY() const;

  /// <summary>
  /// Current keyboard state.
  /// </summary>
  /// <param name="keyCode">The key code.</param>
  /// <returns></returns>
  uint8_t KeyboardState(int keyCode) const;


  /// <summary>
  /// Last keyboard state.
  /// </summary>
  /// <param name="keyCode">The key code.</param>
  /// <returns></returns>
  uint8_t LastKeyboardState(int keyCode) const;

private:

  std::unique_ptr<IInputHandler> input; 


};
#endif
