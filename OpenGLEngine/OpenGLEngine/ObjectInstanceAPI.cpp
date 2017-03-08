#include "ObjectInstanceAPI.h"
#include "MVCView.h"

void ObjectInstanceAPI::SetTranslation(int instHandle, vec3 const& translation)
{
	GetInstance(instHandle)->SetTranslation(translation);
}

//static MPlayer* player;
static MCamera* camera;// = player->GetCamera();


///Temporary until scene render is exposed to lua.
void ObjectInstanceAPI::TestRender(int instHandle)
{
	ObjectInstance * obj = GetInstance(instHandle);
	
  mat4 projectionMatrix = MVCView::camera->getProjectionMatrix();
  mat4 viewMatrix = MVCView::camera->getViewMatrix();
	mat4 worldMatrix = obj->GetWorldMatrix();
	//mat4 worldMatrix = camera->Get

	ShaderLibrary::GetInstance().BindShader("textured");
	obj->Render(worldMatrix, viewMatrix, projectionMatrix);
	ShaderLibrary::GetInstance().BindDefaultShader();

}

ObjectInstance * ObjectInstanceAPI::GetInstance(int instHandle)
{
	return LuaInstanceManager::GetInstance(instHandle);
}

void ObjectInstanceAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "setTranslation", SetTranslation);
	pContext->ExposeFunction(luaAPIName, "testRender", TestRender);
}