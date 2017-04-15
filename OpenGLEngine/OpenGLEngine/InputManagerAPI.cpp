#include "InputManagerAPI.h"



InputManagerAPI::InputManagerAPI()
{
}


InputManagerAPI::~InputManagerAPI()
{
}



bool InputManagerAPI::IsKeyDown(int keyCode) 
{
	return InputManager::GetInstance().keyboardState[keyCode] != 0;
}

bool InputManagerAPI::IsKeyUp(int keyCode) 
{
	return !IsKeyDown(keyCode);
}

bool InputManagerAPI::IsKeyPressed(int keyCode) 
{
	if (IsKeyDown(keyCode))
	{
		if (InputManager::GetInstance().lastKeyboardState[keyCode] == 0)
		{
			return true;
		}
	}
	return false;

}

bool InputManagerAPI::IsKeyReleased(int keyCode) 
{
	return IsKeyUp(keyCode) && (InputManager::GetInstance().lastKeyboardState[keyCode] != 0);
}


void InputManagerAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "isKeyDown", IsKeyDown);
	pContext->ExposeFunction(luaAPIName, "isKeyUp", IsKeyUp);
	pContext->ExposeFunction(luaAPIName, "isKeyPressed", IsKeyPressed);
	pContext->ExposeFunction(luaAPIName, "isKeyReleased", IsKeyReleased);
}