#include "ObjectInstanceAPI.h"

void ObjectInstanceAPI::SetTranslation(InstanceHandle instHandle, float in1,float in2, float in3)
{
	vec3 vec(in1, in2, in3);
	GetInstance(instHandle)->SetTranslation(vec);
}

void ObjectInstanceAPI::SetBaseTransform(InstanceHandle instHandle, LuaRef translation, float yaw, float pitch, float roll, LuaRef scale)
{
  vec3 _translation = FromLuaTable<vec3>(translation);
  vec3 _scale = FromLuaTable<vec3>(scale);
  GetInstance(instHandle)->SetBaseTransform(_translation, yaw, pitch, roll, _scale);
}

//static MPlayer* player;
static MCamera* camera;// = player->GetCamera();

void ObjectInstanceAPI::SetOrientation(InstanceHandle instHandle, float in1, float in2, float in3)
{
	GetInstance(instHandle)->SetOrientation(in1, in2, in3);
}

/*
LuaRef ObjectInstanceAPI::GetOrientation(InstanceHandle instHandle, LuaContextHandle contextHandle)
{
	//Gets mat4
	return ToLuaTable(GetInstance(instHandle)->GetOrientation(),contextHandle);
}
*/

LuaRef ObjectInstanceAPI::Forward(InstanceHandle instHandle, LuaContextHandle cHandle)
{
	auto inst = GetInstance(instHandle);

	return ToLuaTable(inst->Forward(), cHandle);
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


void ObjectInstanceAPI::LookAt(InstanceHandle instHandle, LuaRef upVector, LuaRef targetVec3)
{
	vec3 target = FromLuaTable<vec3>(targetVec3);
	vec3 upVec = FromLuaTable<vec3>(upVector);

	auto inst = LuaObjectInstanceManager::GetInstance(instHandle);
	inst->LookAt(target, upVec);
 // vec3 translation = inst->GetTranslation();
	//inst->SetTransform(glm::inverse(glm::lookAt(translation, target, vec3(0, 1, 0))));
}

LuaRef ObjectInstanceAPI::GetBoundingBox(InstanceHandle instHandle, LuaContextHandle contextHandle)
{
  auto inst = LuaObjectInstanceManager::GetInstance(instHandle);
  return ToLuaTable(inst->GetAlignedBoundingBox(), contextHandle);
}

void ObjectInstanceAPI::SetAnimationSection(InstanceHandle instHandle, float startTime, float sectionLength)
{
  auto inst = LuaObjectInstanceManager::GetInstance(instHandle);
  inst->SetAnimationSection(startTime, sectionLength);
}

void ObjectInstanceAPI::SetAnimationStartTime(InstanceHandle instHandle, float time)
{
  auto inst = LuaObjectInstanceManager::GetInstance(instHandle);
  inst->SetAnimationStartTime(time);
}

void ObjectInstanceAPI::SetAnimationSpeed(InstanceHandle instHandle, float speed)
{
  auto inst = LuaObjectInstanceManager::GetInstance(instHandle);
  inst->SetAnimationSpeed(speed);
}

void ObjectInstanceAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "setTranslation", SetTranslation);
	pContext->ExposeFunction(luaAPIName, "setOrientation", SetOrientation);
	pContext->ExposeFunction(luaAPIName, "setScale", SetScale);
	pContext->ExposeFunction(luaAPIName, "getScale", GetScale);
	pContext->ExposeFunction(luaAPIName, "getTranslation", GetTranslation);
	pContext->ExposeFunction(luaAPIName, "forward", Forward);
	pContext->ExposeFunction(luaAPIName, "lookAt", LookAt);
  pContext->ExposeFunction(luaAPIName, "getBoundingBox", GetBoundingBox);
	pContext->ExposeFunction(luaAPIName, "setAnimation", SetAnimation);
  pContext->ExposeFunction(luaAPIName, "setBaseTransform", SetBaseTransform);
  pContext->ExposeFunction(luaAPIName, "setAnimationSection", SetAnimationSection);
  pContext->ExposeFunction(luaAPIName, "setAnimationStartTime", SetAnimationStartTime);
  pContext->ExposeFunction(luaAPIName, "setAnimationSpeed", SetAnimationSpeed);
}

