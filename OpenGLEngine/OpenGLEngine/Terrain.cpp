#include "Terrain.h"

Terrain::Terrain(uint terrainWidth, uint terrainHeight, float heightScale, float textureTileCount, string const& filepath) 
  : m_terrainWidth(terrainWidth)
  , m_terrainHeight(terrainHeight)
  , m_heightScale(heightScale)
  , m_textureTileCount(textureTileCount)
{
  m_pHeightMap = new HeightMap(filepath);
  m_xBlockScale = terrainWidth / (m_pHeightMap->GetWidth() - 1);
  m_yBlockScale = terrainHeight / (m_pHeightMap->GetHeight() - 1);
  GenerateTerrainVertices();
  GenerateTerrainIndices();
}

void Terrain::GenerateTerrainIndices()
{
  /* int numQuads = (m_pHeightMap->GetWidth() - 1) * (m_pHeightMap->GetHeight() - 1);

   for (int i = 0; i < numQuads; i++)
   {
     for (int j = 0; j < 6; j++)
     {
       m_indices.push_back((i * 6) + j);
     }
   }*/


}

void Terrain::GenerateSmoothNormals()
{

}

void Terrain::GenerateTerrainVertices()
{
  uint width = m_pHeightMap->GetWidth() - 1;
  uint height = m_pHeightMap->GetHeight() - 1;

  uint numVerts = width * height * 6;

  m_vertices.reserve(numVerts);
  m_normals.reserve(numVerts);
  m_texCoords.reserve(numVerts);
  m_indices.reserve(numVerts);

  vec3 leftCorner;
  vec3 rightCorner;
  vec3 bottomLeftCorner;
  vec3 bottomRightCorner;

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      float heightValueL = m_pHeightMap->GetHeightValue(vec2(j, i));
      float heightValueR = m_pHeightMap->GetHeightValue(vec2((j + 1), i));
      float heightValueBL = m_pHeightMap->GetHeightValue(vec2(j, (i + 1)));
      float heightValueBR = m_pHeightMap->GetHeightValue(vec2((j + 1), (i + 1)));

      //Left corner
      leftCorner.x = j * m_blockScale;
      leftCorner.y = heightValueL * m_heightScale;
      leftCorner.z = i * m_blockScale;
      //Right corner
      rightCorner.x = (j + 1) * m_blockScale;
      rightCorner.y = heightValueR * m_heightScale;
      rightCorner.z = i * m_blockScale;
      //Bottom left corner
      bottomLeftCorner.x = j * m_blockScale;
      bottomLeftCorner.y = heightValueBL * m_heightScale;
      bottomLeftCorner.z = (i + 1) * m_blockScale;
      //Bottom right corner
      bottomRightCorner.x = (j + 1) * m_blockScale;
      bottomRightCorner.y = heightValueBR * m_heightScale;
      bottomRightCorner.z = (i + 1) * m_blockScale;

      m_vertices.push_back(rightCorner);
      m_vertices.push_back(leftCorner);
      m_vertices.push_back(bottomLeftCorner);

      m_vertices.push_back(bottomLeftCorner);
      m_vertices.push_back(bottomRightCorner);
      m_vertices.push_back(rightCorner);
    }
  }
}

void Terrain::GenerateTerrainVertex()
{
  uint width = m_pHeightMap->GetWidth();
  uint height = m_pHeightMap->GetHeight();
  uint numVerts = width * height;
  vec3 vertex = vec3(0);

  m_vertices.resize(numVerts);

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      float heightValue = m_pHeightMap->GetHeightValueAtPixel(vec2(j, i));
      vertex.x = j * m_xBlockScale;
      vertex.y = heightValue * m_heightScale;
      vertex.z = i * m_yBlockScale;
      m_vertices[(i*width)+j] = vertex;
    }
  }
}

void Terrain::GenerateTerrainIndex()
{
  uint width = m_pHeightMap->GetWidth() - 1;
  uint height = m_pHeightMap->GetHeight() - 1;

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      uint indexValueL = ((i*width) + j);
      float indexValueR = ((i*width) + (j+1));  
      float indexValueBL = ((i+1)*width) + j;  
      float indexValueBR = (((i+1)*width) + (j + 1));

      m_indices.push_back(indexValueR);
      m_indices.push_back(indexValueL);
      m_indices.push_back(indexValueBL);
        
      m_indices.push_back(indexValueBL);
      m_indices.push_back(indexValueBR);
      m_indices.push_back(indexValueR);
    }
  }
}

void Terrain::GenerateTerrainTexCoords()
{
  for(int i = 0; i < )
}

void Terrain::SaveTerrainToOBJ(const string& filepath)
{
  OBJWriter::SaveMeshToOBJ(*this, filepath);
}

HeightMap* Terrain::GetHeightMap()
{
  return m_pHeightMap;
}

float Terrain::GetXBlockScale() const
{
  return m_xBlockScale;
}

float Terrain::GetYBlockScale() const
{
  return m_yBlockScale;
}

float Terrain::GetHeightScale() const
{
  return m_heightScale;
}

std::vector<vec3> const& Terrain::GetVertices() const
{
  return m_vertices;
}

std::vector<vec3> const& Terrain::GetNormals() const
{
  return m_normals;
}

std::vector<int> const& Terrain::GetIndices() const
{
  return m_indices;
}
