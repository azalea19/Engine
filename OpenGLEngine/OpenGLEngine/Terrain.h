#ifndef Terrain_h__
#define Terrain_h__

#include "Types.h"
#include "HeightMap.h"
#include "IMesh.h"
#include "OBJWriter.h"

class Terrain : public IMesh
{
public:

  Terrain(float blockScale, float heightScale, string const& filepath);

  void GenerateTerrainIndices();

  void GenerateTerrainVertices();

  void SaveTerrainToOBJ(const string& filepath);

  HeightMap* GetHeightMap();

  float GetBlockScale() const;
  float GetHeightScale() const;

  float GetHeightValue(vec2i position);

  virtual std::vector<vec3> const& GetVertices() const override;

  virtual std::vector<vec3> const& GetNormals() const override;

  virtual std::vector<int> const& GetIndices() const override;

private:

  std::vector<vec3> m_vertices;
  std::vector<vec3> m_normals;
  std::vector<int> m_indices;
  std::vector<vec2> m_texCoords;

  HeightMap* m_pHeightMap;
  float m_heightScale;
  float m_blockScale;

};


#endif // Terrain_h__
