#pragma once
#include "InputManager.h"

#include "LuaContext.h"
#include "LuaManager.h"


/**
* @file   InputManagerAPI.h
* @Author Elizabeth Haynes
* @date   S1, 2017
* @brief  Lua API for the input manager.
*
*/

class InputManagerAPI
{
public:

	
	/// <summary>
	/// Get mouse delta X through lua API.
	/// </summary>
	/// <returns>int</returns>
	static int MouseDeltaX();

	/// <summary>
	/// Get mouse delta Y through lua API.
	/// </summary>
	/// <returns>int</returns>
	static int MouseDeltaY();

	/// <summary>
	/// Checks if key is down in input through lua API.
	/// </summary>
	/// <param name="keyCode">sdl key code</param>
	/// <returns>bool</returns>
	static bool IsKeyDown(int keyCode);


	/// <summary>
	/// Checks if key is up in input through lua API.
	/// </summary>
	/// <param name="keyCode">sdl key code</param>
	/// <returns>int</returns>
	static bool IsKeyUp(int keyCode);

	/// <summary>
	/// Checks if key is pressed in input through lua API.
	/// </summary>
	/// <param name="keyCode">sdl key code</param>
	/// <returns>int</returns>
	static bool IsKeyPressed(int keyCode);

	/// <summary>
	/// Checks if key is released in input through lua API.
	/// </summary>
	/// <param name="keyCode">sdl key code</param>
	/// <returns>int</returns>
	static bool IsKeyReleased(int keyCode);

	/// <summary>
	/// Exposes class to lua as API
	/// </summary>
	/// <param name="contextHandle">Lua context handle</param
	/// <param name="luaAPIName">Name of the API</param>
	/// <returns>int</returns>
	static void Expose(LuaContextHandle contextHandle, string luaAPIName);

private:

  std::unique_ptr<IInputHandler> input;

};

