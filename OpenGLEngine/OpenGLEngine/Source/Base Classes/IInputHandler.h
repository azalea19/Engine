#ifndef IInputHandler_h__
#define IInputHandler_h__


class IInputHandler
{

public:

  /// <summary>
  /// Updates this instance.
  /// </summary>
  virtual void Update() = 0;


  /// <summary>
  /// Determines whether [is key down] [the specified key code].
  /// </summary>
  /// <param name="keyCode">The key code.</param>
  /// <returns>
  ///   <c>true</c> if [is key down] [the specified key code]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsKeyDown(int keyCode) const = 0;



  /// <summary>
  /// Determines whether [is key up] [the specified key code].
  /// </summary>
  /// <param name="keyCode">The key code.</param>
  /// <returns>
  ///   <c>true</c> if [is key up] [the specified key code]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsKeyUp(int keyCode) const = 0;


  /// <summary>
  /// Determines whether [is key pressed] [the specified key code].
  /// </summary>
  /// <param name="keyCode">The key code.</param>
  /// <returns>
  ///   <c>true</c> if [is key pressed] [the specified key code]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsKeyPressed(int keyCode) const = 0;


  /// <summary>
  /// Determines whether [is key released] [the specified key code].
  /// </summary>
  /// <param name="keyCode">The key code.</param>
  /// <returns>
  ///   <c>true</c> if [is key released] [the specified key code]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsKeyReleased(int keyCode) const = 0;


  /// <summary>
  /// Determines whether [is mouse down left].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse down left]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsMouseDownLeft() const = 0;


  /// <summary>
  /// Determines whether [is mouse up left].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse up left]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsMouseUpLeft() const = 0;


  /// <summary>
  /// Determines whether [is mouse pressed left].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse pressed left]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsMousePressedLeft() const = 0;


  /// <summary>
  /// Determines whether [is mouse released left].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse released left]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsMouseReleasedLeft() const = 0;


  /// <summary>
  /// Determines whether [is mouse down right].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse down right]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsMouseDownRight() const = 0;


  /// <summary>
  /// Determines whether [is mouse up right].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse up right]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsMouseUpRight() const = 0;


  /// <summary>
  /// Determines whether [is mouse pressed right].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse pressed right]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsMousePressedRight() const = 0;


  /// <summary>
  /// Determines whether [is mouse released right].
  /// </summary>
  /// <returns>
  ///   <c>true</c> if [is mouse released right]; otherwise, <c>false</c>.
  /// </returns>
  virtual bool IsMouseReleasedRight() const = 0;


  /// <summary>
  /// Gets the change in x.
  /// </summary>
  /// <returns>int32_t</returns>
  virtual int32_t MouseDeltaX() const = 0;


  /// <summary>
  /// Gets the change in y.
  /// </summary>
  /// <returns>int32_t</returns>
  virtual int32_t MouseDeltaY() const = 0;


  /// <summary>
  /// Gets the state of the keyboard at the key code.
  /// </summary>
  /// <param name="keyCode">The key code.</param>
  /// <returns></returns>
  virtual uint8_t KeyboardState(int keyCode) const = 0;

  /// <summary>
  /// The last state of the keyboard at the key code.
  /// </summary>
  /// <param name="keyCode">The key code.</param>
  /// <returns></returns>
  virtual uint8_t LastKeyboardState(int keyCode) const = 0;

};

#endif // IInputHandler_h__
