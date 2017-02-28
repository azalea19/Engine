#include "ModelLoadingAPI.h"
#include "ModelLibrary.h"
#include "LuaManager.h"

static void LoadModel(string modelName, string modelPath)
{
  //we should probably get rid of that last parameter since i dont think it makes sense anymore
  ModelLibrary::getLib()->addModel(modelName, modelPath, false);
}

void ModelLoadingAPI::Expose(LuaContextHandle contextHandle, string luaAPIName)
{
  LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
  pContext->ExposeFunction(luaAPIName, "LoadModel", LoadModel);
}
