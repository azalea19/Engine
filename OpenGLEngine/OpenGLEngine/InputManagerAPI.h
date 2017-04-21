#pragma once
#include "InputManager.h"

#include "LuaContext.h"
#include "LuaManager.h"

class InputManagerAPI
{
public:

	static void InputManagerAPI::Update();

	
	/// API to get mouse delta X.
	static int InputManagerAPI::MouseDeltaX();

	/// API to get mouse delta Y.
	static int InputManagerAPI::MouseDeltaY();

	static bool IsKeyDown(int keyCode);



	static bool IsKeyUp(int keyCode);


	static bool IsKeyPressed(int keyCode);


	static bool IsKeyReleased(int keyCode);

	static void Expose(LuaContextHandle contextHandle, string luaAPIName);

};

