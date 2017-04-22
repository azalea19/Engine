#ifndef Mesh_h__
#define Mesh_h__

#include "Types.h"
#include "Texture.h"
#include "GeometricPrimitives.h"
#include "Bimap.h"
#include "Material.h"
#include "IMesh.h"

#define MAX_BONES_PER_VERTEX 4

struct aiMesh;

//Each vertex will contain four bone IDs that influence it
struct VertexBoneIDs
{
  int boneIDs[MAX_BONES_PER_VERTEX] = { 0, 0, 0, 0 };
};

struct VertexBoneWeights
{
  float boneWeights[MAX_BONES_PER_VERTEX] = { 0.0f, 0.0f, 0.0f, 0.0f };
};


class Mesh : public IMesh
{

public:
	Mesh();
	Mesh(aiMesh const *pMesh, Bimap<string,int> const& boneLookup);
	string const& GetName() const;
	std::vector<vec2> const& GetTexCoords(TextureType const& texType) const;
  std::vector<vec4> const& GetVertexColours() const;
	std::vector<VertexBoneIDs> const& GetBoneIDs() const;
	std::vector<VertexBoneWeights> const& GetBoneWeights() const;
	int const& GetMaterialIndex() const;
	mAABB const& GetBounds() const;


  int GetVertexColoursCount() const;
  int GetBoneIDCount() const;
  int GetBoneWeightCount() const;


  virtual std::vector<vec3> const& GetVertices() const override;


  virtual std::vector<vec3> const& GetNormals() const override;


  virtual std::vector<int> const& GetIndices() const override;

private:
	string m_name;
	std::vector<vec2> m_texCoords[TT_TextureTypeCount];
	std::vector<vec3> m_vertices;
	std::vector<vec3> m_normals;
  std::vector<vec4> m_vertexColours;
	std::vector<int> m_indices;
	std::vector<VertexBoneIDs> m_boneIDs;
	std::vector<VertexBoneWeights> m_boneWeights;
	mAABB m_bounds;
  int materialIndex;

  bool m_hasVertexColours;

  void LoadTexCoords(aiMesh const *pMesh);
  void LoadVertices(aiMesh const *pMesh);
  void LoadNormals(aiMesh const *pMesh);
  void LoadVertexColours(aiMesh const *pMesh);
  void LoadIndices(aiMesh const *pMesh);
  void LoadBones(aiMesh const *pMesh, Bimap<string,int> const& boneLookup);
  void LoadMaterial(aiMesh const *pMesh);
  void CalculateBounds();
  int GetNextWeightSlot(int vertexIndex);
};

#endif