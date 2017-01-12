#ifndef ForestTerrain_h__
#define ForestTerrain_h__

#include "Terrain.h"
#include "ObjectInstance.h"
#include "Random.h"
#include "ModelLibrary.h"
#include "OBJWriter.h"

class ForestTerrain : public IRenderable, public IMesh
{
public:

  ForestTerrain(int blockScale, int heightScale, string const& filePath, int density);


  void GenerateForest();


  void SaveTerrainToOBJ(const string& filepath) const;


  virtual void Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time) override;


  virtual std::vector<vec3> const& GetVertices() const override;


  virtual std::vector<vec3> const& GetNormals() const override;


  virtual std::vector<int> const& GetIndices() const override;
  
  //virtual std::vector<vec2> const& GetTexCoords(int index) const override;

private:

  std::vector<ObjectInstance*> m_trees;

  Terrain* m_pLand;

};


#endif // ForestTerrain_h__
