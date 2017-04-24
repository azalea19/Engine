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
	/// <summary>
	/// Exposes the specified context handle.
	/// </summary>
	/// <param name="contextHandle">The context handle.</param>
	/// <param name="luaAPIName">Name of the lua API.</param>
	static void Expose(LuaContextHandle contextHandle, string luaAPIName);
	/// <summary>
	/// Generates the terrain.
	/// </summary>
	/// <param name="terrainWidth">Width of the terrain.</param>
	/// <param name="terrainHeight">Height of the terrain.</param>
	/// <param name="heightMapSize">Size of the height map.</param>
	/// <param name="heightScale">The height scale.</param>
	/// <param name="heightMapPath">The height map path.</param>
	/// <param name="objPath">The object path.</param>
	/// <param name="contextHandle">The context handle.</param>
	/// <returns></returns>
	static LuaRef GenerateTerrain(uint terrainWidth, uint terrainHeight, uint heightMapSize, float heightScale, string const& heightMapPath, string const& objPath, LuaContextHandle contextHandle);
};

