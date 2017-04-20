#ifndef CameraAPI_h__
#define CameraAPI_h__


#include "types.h"
#include "LuaContext.h"
#include "InstanceManager.h"
#include "MCamera.h"
#include "MathAPI.h"

class CameraAPI
{
public:


	static InstanceHandle AddNewInstance();
	static void SetYaw(InstanceHandle handle, float yaw);
	static void SetPitch(InstanceHandle handle, float pitch);
	static float GetYaw(InstanceHandle handle);
	static float GetPitch(InstanceHandle handle);
	static LuaRef Forward(InstanceHandle handle);
	static LuaRef Right(InstanceHandle handle);
	static void SetPosition(InstanceHandle handle, float x, float y, float z);



    static void Expose(LuaContextHandle contextHandle, string luaAPIName);
};


#endif // CameraAPI_h__
