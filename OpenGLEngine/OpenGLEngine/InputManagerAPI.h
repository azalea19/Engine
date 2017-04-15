#pragma once
#include "InputManager.h"

#include "LuaContext.h"
#include "LuaManager.h"

class InputManagerAPI
{
public:
	InputManagerAPI();
	~InputManagerAPI();

	static bool IsKeyDown(int keyCode);



	static bool IsKeyUp(int keyCode);


	static bool IsKeyPressed(int keyCode);


	static bool IsKeyReleased(int keyCode);

	static void Expose(LuaContextHandle contextHandle, string luaAPIName);

};

