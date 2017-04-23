#include "LuaManager.h"
#include "OBJWriter.h"
#include <vector>
#include "mathAPI.h"


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
	static LuaRef GenerateTerrain(uint terrainWidth, uint terrainHeight, uint heightMapSize, float heightScale, string const& heightMapPath, string const& objPath, LuaContextHandle contextHandle);
};

