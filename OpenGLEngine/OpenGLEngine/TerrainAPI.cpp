#ifndef TerrainAPI_h__
#define TerrainAPI_h__

#include "TerrainAPI.h"
#include "Terrain.h"
#include "OBJWriter.h"

void TerrainAPI::Expose(LuaContextHandle contextHandle, string luaAPIName) 
{
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "generateTerrain", GenerateTerrain);
}

void TerrainAPI::GenerateTerrain(uint terrainWidth, uint terrainHeight, float heightScale, string const& heightMapPath, string const& objPath) 
{
  Terrain tempTerrain{ terrainWidth, terrainHeight, heightScale, heightMapPath };
	OBJWriter::SaveMeshToOBJ(tempTerrain, objPath);
}

#endif // TerrainAPI_h__