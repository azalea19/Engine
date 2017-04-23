#include "ObjectInstanceAPI.h"

void ObjectInstanceAPI::SetTranslation(InstanceHandle instHandle, float in1,float in2, float in3)
{
	vec3 vec(in1, in2, in3);
	GetInstance(instHandle)->SetTranslation(vec);
}

//static MPlayer* player;
static MCamera* camera;// = player->GetCamera();

void ObjectInstanceAPI::SetOrientation(InstanceHandle instHandle, float in1, float in2, float in3)
{
	GetInstance(instHandle)->SetOrientation(in1, in2, in3);
}

void ObjectInstanceAPI::SetScale(InstanceHandle instHandle, float in1, float in2, float in3)
{
	vec3 vec(in1, in2, in3);
	GetInstance(instHandle)->SetScale(vec);
}

void ObjectInstanceAPI::SetAnimation(InstanceHandle instHandle, int isAnimated)
{
	GetInstance(instHandle)->SetActiveAnimation(isAnimated);
}

ObjectInstance * ObjectInstanceAPI::GetInstance(InstanceHandle instHandle)
{
	return LuaObjectInstanceManager::GetInstance(instHandle);
}

LuaRef ObjectInstanceAPI::GetScale(InstanceHandle instHandle, LuaContextHandle cHandle)
{
	return ToLuaTable(LuaObjectInstanceManager::GetInstance(instHandle)->GetScale(),cHandle);

}

LuaRef ObjectInstanceAPI::GetTranslation(InstanceHandle instHandle, LuaContextHandle cHandle)
{
	return ToLuaTable(LuaObjectInstanceManager::GetInstance(instHandle)->GetTranslation(), cHandle);

}

void ObjectInstanceAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "setTranslation", SetTranslation);
	pContext->ExposeFunction(luaAPIName, "setOrientation", SetOrientation);
	pContext->ExposeFunction(luaAPIName, "setScale", SetScale);
	pContext->ExposeFunction(luaAPIName, "getScale", GetScale);
	pContext->ExposeFunction(luaAPIName, "getTranslation", GetTranslation);

	pContext->ExposeFunction(luaAPIName, "setAnimation", SetAnimation);
}