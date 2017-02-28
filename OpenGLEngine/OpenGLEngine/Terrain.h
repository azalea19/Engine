#ifndef Terrain_h__
#define Terrain_h__

#include "Types.h"
#include "HeightMap.h"
#include "IMesh.h"
#include "OBJWriter.h"

class Terrain : public IMesh
{
public:

  Terrain(uint terrainWidth, uint terrainHeight, float heightScale, float textureTileCount, string const& filepath);

  void GenerateTerrainIndices();

  void GenerateTerrainVertices();

  void GenerateTerrainVertex();

  void GenerateTerrainIndex();

  void GenerateTerrainTexCoords();

  void GenerateSmoothNormals();

  void SaveTerrainToOBJ(const string& filepath);

  HeightMap* GetHeightMap();

  float GetXBlockScale() const;

  float GetYBlockScale() const;

  float GetHeightScale() const;

  virtual std::vector<vec3> const& GetVertices() const override;

  virtual std::vector<vec3> const& GetNormals() const override;

  virtual std::vector<int> const& GetIndices() const override;

  void Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time) const;

private:

  std::vector<vec3> m_vertices;
  std::vector<vec3> m_normals;
  std::vector<int> m_indices;
  std::vector<vec2> m_texCoords;

  HeightMap* m_pHeightMap;
  float m_heightScale;

  float m_xBlockScale;
  float m_yBlockScale;

  float m_terrainWidth;
  float m_terrainHeight;

  float m_textureTileCount;

};


#endif // Terrain_h__
