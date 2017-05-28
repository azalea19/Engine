#include "ForestTerrain.h"
#include "MMath.h"


void ForestTerrain::SaveTerrainToOBJ(const string& filepath) const
{
  OBJWriter::SaveMeshToOBJ(*this, filepath);
}

ForestTerrain::ForestTerrain(uint terrainWidth, uint terrainHeight, float heightScale, float textureTileCount, string const& filePath, string const& alphapath, int density)
{
  //m_pLand = new Terrain(terrainWidth, terrainHeight, heightScale, filePath, alphapath, 0);
  //GenerateForest();
}

void ForestTerrain::GenerateForest()
{
  static const char* treeNames[] = { "PalmTree", "BambooPalm", "GroundPalm", "SmallPlant", "HighTree" };
  int width = m_pLand->GetHeightMap()->GetWidth();
  int height = m_pLand->GetHeightMap()->GetHeight();

  ObjectInstance* pTree;
  float x_bs = m_pLand->GetXBlockScale();
  float y_bs = m_pLand->GetYBlockScale();
  float hs = m_pLand->GetHeightScale();

  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
		
      float heightAtPixel = m_pLand->GetHeightMap()->GetHeightValueAtPixel(vec2(x, y));
      float success = RandomFloat(0, 1);
      if (success < pow(heightAtPixel, 1) * 0.1f)
      {
        string treeName = treeNames[RandomInt(0, sizeof(treeNames) / sizeof(treeNames[0]))];
        pTree = ModelLibrary::GetInstance().GetObjectInstance(treeName);
        pTree->SetTranslation(vec3(x*x_bs, heightAtPixel*hs, y*y_bs));
        float yaw = RandomFloat(0, 360);
        float scale = RandomFloat(0.5f, 1);
        pTree->SetYaw(yaw);
        pTree->SetScale(vec3(scale, scale, scale));
        m_trees.push_back(pTree);
      }
    }
  }
}

void ForestTerrain::Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time)
{
  for (int i = 0; i < m_trees.size(); i++)
  {
    m_trees[i]->Render(worldMatrix, viewMatrix, projectionMatrix);
  }
}

std::vector<vec3> const& ForestTerrain::GetVertices() const
{
  return m_pLand->GetVertices();
}

std::vector<vec3> const& ForestTerrain::GetNormals() const
{
  return m_pLand->GetNormals();
}

std::vector<int> const& ForestTerrain::GetIndices() const
{
  return m_pLand->GetIndices();
}
