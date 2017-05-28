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

LuaRef TerrainAPI::GenerateTerrain(uint terrainWidth, uint terrainHeight, uint heightMapSize, float heightScale, string const& heightMapPath, string const& alphaPath, string const& objPath, LuaContextHandle contextHandle) 
{
  Terrain tempTerrain(terrainWidth, terrainHeight, heightScale, heightMapPath, alphaPath);
	std::vector<float> hmData;
  std::vector<float> alphaData;

  float temp;
  float temp2;

	for (int y = 0; y < heightMapSize; y++)
	{
		for(int x = 0; x < heightMapSize; x++)
		{
			temp = tempTerrain.GetHeightMap()->GetHeightValueAtPixel(vec2(x,y)) * heightScale;
      temp2 = tempTerrain.GetAlphaMap()->GetHeightValueAtPixel(vec2(x, y));
			hmData.push_back(temp);
      alphaData.push_back(temp2);
		}
	}
	LuaRef result = ToLuaTable(hmData, alphaData, heightMapSize, heightMapSize, contextHandle);
	OBJWriter tempWriter;
	tempWriter.SaveMeshToOBJ(tempTerrain, objPath);

	return result;
}



#endif // TerrainAPI_h__
