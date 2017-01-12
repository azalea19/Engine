#include "Terrain.h"

Terrain::Terrain(float blockScale, float heightScale, string const& filepath) 
  : m_blockScale(blockScale)
  , m_heightScale(heightScale)
{
  m_pHeightMap = new HeightMap(filepath);
  GenerateTerrainVertices();
  GenerateTerrainIndices();
}

void Terrain::GenerateTerrainIndices()
{
  int numQuads = (m_pHeightMap->GetWidth() - 1) * (m_pHeightMap->GetHeight() - 1);

  for (int i = 0; i < numQuads; i++)
  {
    for (int j = 0; j < 6; j++)
    {
      m_indices.push_back((i * 6) + j);
    }
  }
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

void Terrain::SaveTerrainToOBJ(const string& filepath)
{
  OBJWriter::SaveMeshToOBJ(*this, filepath);
}

HeightMap* Terrain::GetHeightMap()
{
  return m_pHeightMap;
}

float Terrain::GetBlockScale() const
{
  return m_blockScale;
}

float Terrain::GetHeightScale() const
{
  return m_heightScale;
}

float Terrain::GetHeightValue(vec2i position)
{
  return m_pHeightMap->GetHeightValue(position);
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
