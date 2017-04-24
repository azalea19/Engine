#include "ModelLibraryAPI.h"


void ModelLibraryAPI::AddModel(string const& name, string const& path, bool normalized)
{
	ModelLibrary::GetInstance().AddModel(name, path, normalized);
}

void ModelLibraryAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "addModel", AddModel);
}
