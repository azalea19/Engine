#include "CameraAPI.h"

InstanceHandle CameraAPI::AddNewInstance()
{
	return InstanceManager<MCamera>().GetInstance().AddNewInstance();
}

void CameraAPI::SetYaw(InstanceHandle handle, float yaw)
{
	InstanceManager<MCamera>().GetInstance().GetInst(handle)->SetYaw(yaw);
}
void CameraAPI::SetPitch(InstanceHandle handle, float pitch)
{
	InstanceManager<MCamera>().GetInstance().GetInst(handle)->SetPitch(pitch);

}
float CameraAPI::GetYaw(InstanceHandle handle)
{
	return InstanceManager<MCamera>().GetInstance().GetInst(handle)->GetYaw();

}
float CameraAPI::GetPitch(InstanceHandle handle)
{
	return InstanceManager<MCamera>().GetInstance().GetInst(handle)->GetPitch();

}
LuaRef CameraAPI::Forward(InstanceHandle handle)
{
	return ToLuaTable(InstanceManager<MCamera>().GetInstance().GetInst(handle)->Forward());

}
LuaRef CameraAPI::Right(InstanceHandle handle)
{
	return ToLuaTable(InstanceManager<MCamera>().GetInstance().GetInst(handle)->Right());

}
void CameraAPI::SetPosition(InstanceHandle handle, float x, float y, float z)
{
	InstanceManager<MCamera>().GetInstance().GetInst(handle)->SetPosition( vec3(x,y,z));

}

void CameraAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "addNewInstance", AddNewInstance);
	pContext->ExposeFunction(luaAPIName, "setYaw", SetYaw);
	pContext->ExposeFunction(luaAPIName, "getYaw", GetYaw);
	pContext->ExposeFunction(luaAPIName, "getPitch", GetPitch);
	pContext->ExposeFunction(luaAPIName, "setPitch", SetPitch);
	pContext->ExposeFunction(luaAPIName, "forward", Forward);
	pContext->ExposeFunction(luaAPIName, "right", Right);
	pContext->ExposeFunction(luaAPIName, "setPosition", SetPosition);

}