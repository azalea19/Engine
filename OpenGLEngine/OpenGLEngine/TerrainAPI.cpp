#pragma once
#include "TerrainAPI.h"

void TerrainAPI::Expose(LuaContextHandle contextHandle, string luaAPIName) {
	LuaContext* pContext = LuaManager::GetInstance().GetContext(contextHandle);
	pContext->ExposeFunction(luaAPIName, "generateTerrain", GenerateTerrain);
}

void TerrainAPI::GenerateTerrain(uint terrainWidth, uint terrainHeight, float heightScale, string const& heightMapPath, string const& objPath) {
	Terrain tempTerrain(terrainWidth, terrainHeight, heightScale, heightMapPath);
	OBJWriter tempWriter;
	tempWriter.SaveMeshToOBJ(tempTerrain, objPath);
}