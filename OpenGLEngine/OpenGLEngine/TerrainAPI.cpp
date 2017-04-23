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

LuaRef TerrainAPI::GenerateTerrain(uint terrainWidth, uint terrainHeight, uint heightMapSize, float heightScale, string const& heightMapPath, string const& objPath, LuaContextHandle contextHandle) {
	Terrain tempTerrain(terrainWidth, terrainHeight, heightScale, heightMapPath);
	std::vector<float> data;
	float temp;
	for (int i = 0; i < heightMapSize; i++)
	{
		for(int k = 0; k < heightMapSize; k++)
		{
			temp = ((tempTerrain.GetHeightMap())->GetHeightValueAtPixel(vec2(i,k))) * heightScale;
			data.push_back(temp);
		}
	}
	LuaRef result = ToLuaTable(data, heightMapSize, heightMapSize, contextHandle);
	OBJWriter tempWriter;
	tempWriter.SaveMeshToOBJ(tempTerrain, objPath);

	return result;
}

#endif // TerrainAPI_h__
