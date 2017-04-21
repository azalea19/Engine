#include "CameraAPI.h"
#include "MCamera.h"

InstanceHandle CameraAPI::AddNewInstance()
{
	InstanceManager<MCamera> camMan = InstanceManager<MCamera>().GetInstance();
	InstanceHandle handle = camMan.AddNewInstance();

	camMan.GetInst(handle)->SetPosition(vec3(0,0,1));
	camMan.GetInst(handle)->Forward();
	camMan.GetInst(handle)->Left();
	camMan.GetInst(handle)->Up();
	camMan.GetInst(handle)->Right();
	camMan.GetInst(handle)->Down();


	return handle;

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

LuaRef CameraAPI::Forward(InstanceHandle handle, LuaContextHandle contextHandle)
{
	return ToLuaTable(InstanceManager<MCamera>().GetInstance().GetInst(handle)->Forward(), contextHandle);

}

LuaRef CameraAPI::Right(InstanceHandle handle, LuaContextHandle contextHandle)
{
	return ToLuaTable(InstanceManager<MCamera>().GetInstance().GetInst(handle)->Right(), contextHandle);

}

void CameraAPI::SetPosition(InstanceHandle handle, float x, float y, float z)
{
	InstanceManager<MCamera>().GetInstance().GetInst(handle)->SetPosition( vec3(x,y,z));

}
LuaRef CameraAPI::GetPosition(InstanceHandle handle, LuaContextHandle contextHandle)
{
	return ToLuaTable(InstanceManager<MCamera>().GetInstance().GetInst(handle)->GetTranslation(),contextHandle);

}

LuaRef CameraAPI::GetViewMatrix(InstanceHandle handle, LuaContextHandle contextHandle)
{
	return ToLuaTable(InstanceManager<MCamera>().GetInstance().GetInst(handle)->getViewMatrix(), contextHandle);

}

LuaRef CameraAPI::GetProjectionMatrix(InstanceHandle handle, LuaContextHandle contextHandle)
{
	return ToLuaTable(InstanceManager<MCamera>().GetInstance().GetInst(handle)->getProjectionMatrix(), contextHandle);

}

void CameraAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "addNewInstance", AddNewInstance);
	pContext->ExposeFunction(luaAPIName, "getProjectionMatrix", GetProjectionMatrix);
	pContext->ExposeFunction(luaAPIName, "getViewMatrix", GetViewMatrix);

	pContext->ExposeFunction(luaAPIName, "addNewInstance", AddNewInstance);

	pContext->ExposeFunction(luaAPIName, "setYaw", SetYaw);
	pContext->ExposeFunction(luaAPIName, "getYaw", GetYaw);
	pContext->ExposeFunction(luaAPIName, "getPitch", GetPitch);
	pContext->ExposeFunction(luaAPIName, "setPitch", SetPitch);
	pContext->ExposeFunction(luaAPIName, "forward", Forward);
	pContext->ExposeFunction(luaAPIName, "right", Right);
	pContext->ExposeFunction(luaAPIName, "setPosition", SetPosition);
	pContext->ExposeFunction(luaAPIName, "getPosition", GetPosition);


}