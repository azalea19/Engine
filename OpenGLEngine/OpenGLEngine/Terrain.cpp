#include "Terrain.h"
#include "ShaderLibrary.h"
#include "Texture.h"
#include "OBJWriter.h"

Terrain::Terrain(uint terrainWidth, uint terrainHeight, float heightScale, string const& filepath)
  : m_terrainWidth(terrainWidth)
  , m_terrainHeight(terrainHeight)
  , m_heightScale(heightScale)
{
  m_pHeightMap = new HeightMap(filepath);
  m_xBlockScale = terrainWidth / (float)(m_pHeightMap->GetWidth() - 1);
  m_yBlockScale = terrainHeight / (float)(m_pHeightMap->GetHeight() - 1);
  CreateMesh();
}

void Terrain::GenerateTexCoords()
{
  uint width = m_pHeightMap->GetWidth();
  uint height = m_pHeightMap->GetHeight();
  uint numVerts = width * height;
  m_texCoords.resize(numVerts);

  float scaleX = 1.f / (width - 1);
	 float scaleY = 1.f / (height - 1);

  for (uint y = 0; y < height; y++)
  {
    for (uint x = 0; x < width; x++)
    {
      m_texCoords[(y*width) + x] = vec2(x*scaleX, y*scaleY);
    }
  }
}

void Terrain::GenerateNormals()
{
  int height = GetHeightMap()->GetHeight();
  int width = GetHeightMap()->GetWidth();

  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      float y00 = GetHeightMap()->GetHeightValueAtPixel(vec2(x, y));
      float y10 = GetHeightMap()->GetHeightValueAtPixel(vec2(x + 1, y));
      float y11 = GetHeightMap()->GetHeightValueAtPixel(vec2(x + 1, y + 1));
      float y01 = GetHeightMap()->GetHeightValueAtPixel(vec2(x, y + 1));

      glm::vec3 norm = glm::cross(glm::normalize(glm::vec3(x + 1, y10, y) - glm::vec3(x, y00, y)), glm::normalize(glm::vec3(x, y01, y + 1) - glm::vec3(x, y00, y)));
      glm::vec3 norm2 = glm::cross(glm::normalize(glm::vec3(x + 1, y11, (y + 1)) - glm::vec3(x + 1, y10, y)), glm::normalize(glm::vec3(x, y01, y + 1) - glm::vec3(x + 1, y10, y)));

      m_normals.push_back(norm);
      m_normals.push_back(norm);
      m_normals.push_back(norm);
      m_normals.push_back(norm2);
      m_normals.push_back(norm2);
      m_normals.push_back(norm2);
    }
  }
}

void Terrain::GenerateTerrainVertices()
{
  uint width = m_pHeightMap->GetWidth();
  uint height = m_pHeightMap->GetHeight();
  uint numVerts = width * height;
  vec3 vertex = vec3(0);

  m_vertices.resize(numVerts);

  for (uint y = 0; y < height; y++)
  {
    for (uint x = 0; x < width; x++)
    {
      float heightValue = m_pHeightMap->GetHeightValueAtPixel(vec2(x, y));
      vertex.x = x * m_xBlockScale;
      vertex.y = heightValue * m_heightScale;
      vertex.z = y * m_yBlockScale;
      m_vertices[(y*width) + x] = vertex;
    }
  }
}

void Terrain::GenerateTerrainIndices()
{
  uint width = m_pHeightMap->GetWidth();
  uint height = m_pHeightMap->GetHeight();

  for (uint i = 0; i < height - 1; i++)
  {
    for (uint j = 0; j < width - 1; j++)
    {
      uint indexValueL = ((i*width) + j);
      uint indexValueR = ((i*width) + (j + 1));
      uint indexValueBL = ((i + 1)*width) + j;
      uint indexValueBR = (((i + 1)*width) + (j + 1));

      m_indices.push_back(indexValueR);
      m_indices.push_back(indexValueL);
      m_indices.push_back(indexValueBL);

      m_indices.push_back(indexValueBL);
      m_indices.push_back(indexValueBR);
      m_indices.push_back(indexValueR);
    }
  }
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

void Terrain::CreateMesh()
{
  GenerateTerrainVertices();
  GenerateTerrainIndices();
  GenerateNormals();
  GenerateTexCoords();

  glGenBuffers(1, &gVBO);
  glGenBuffers(1, &gNBO);
  glGenBuffers(1, &gIBO);

  glBindBuffer(GL_ARRAY_BUFFER, gVBO);
  glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GLfloat), m_vertices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ARRAY_BUFFER, gNBO);
  glBufferData(GL_ARRAY_BUFFER, m_normals.size() * 3 * sizeof(GLfloat), m_normals.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ARRAY_BUFFER, gIBO);
  glBufferData(GL_ARRAY_BUFFER, m_indices.size() * sizeof(GLint), m_indices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}



