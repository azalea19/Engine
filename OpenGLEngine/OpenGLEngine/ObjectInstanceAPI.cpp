#include "ObjectInstanceAPI.h"

void ObjectInstanceAPI::SetTranslation(InstanceHandle instHandle, float in1,float in2, float in3)
{
	vec3 vec(in1, in2, in3);
	GetInstance(instHandle)->SetTranslation(vec);
}

//static MPlayer* player;
static MCamera* camera;// = player->GetCamera();


ObjectInstance * ObjectInstanceAPI::GetInstance(InstanceHandle instHandle)
{
	return LuaInstanceManager::GetInstance(instHandle);
}

void ObjectInstanceAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "setTranslation", SetTranslation);
}