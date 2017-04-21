#pragma once
#include "Terrain.h"
#include "LuaManager.h"
#include "OBJWriter.h"

class TerrainAPI
{
public:
	static void Expose(LuaContextHandle contextHandle, string luaAPIName);
	static void GenerateTerrain(uint terrainWidth, uint terrainHeight, float heightScale, string const& heightMapPath, string const& objPath);
};

