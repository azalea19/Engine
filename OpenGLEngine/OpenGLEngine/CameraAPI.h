#ifndef CameraAPI_h__
#define CameraAPI_h__


#include "types.h"
#include "LuaContext.h"
#include "InstanceManager.h"
#include "MathAPI.h"

class CameraAPI
{
public:


	static InstanceHandle AddNewInstance();
	static void SetYaw(InstanceHandle handle, float yaw);
	static void SetPitch(InstanceHandle handle, float pitch);
	static float GetYaw(InstanceHandle handle);
	static float GetPitch(InstanceHandle handle);
	static LuaRef GetViewMatrix(InstanceHandle handle, LuaContextHandle contextHandle);
	static LuaRef GetProjectionMatrix(InstanceHandle handle, LuaContextHandle contextHandle);
	static LuaRef Forward(InstanceHandle handle, LuaContextHandle contextHandle);
	static LuaRef Right(InstanceHandle handle, LuaContextHandle contextHandle);
	static void SetPosition(InstanceHandle handle, float x, float y, float z);



    static void Expose(LuaContextHandle contextHandle, string luaAPIName);
};


#endif // CameraAPI_h__
