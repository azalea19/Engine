#pragma once
#include "Terrain.h"
#include "LuaManager.h"
#include "OBJWriter.h"


/**
* @file   TerrainAPI.h
* @Author Nathan Gane
* @date   S1, 2017
* @brief  Lua API for the Terrain class.
*
*/

class TerrainAPI
{
public:
	static void Expose(LuaContextHandle contextHandle, string luaAPIName);
	static void GenerateTerrain(uint terrainWidth, uint terrainHeight, float heightScale, string const& heightMapPath, string const& objPath);
};

