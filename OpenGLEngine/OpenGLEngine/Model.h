#ifndef Model_h__
#define Model_h__

#include "Types.h"
#include <unordered_map>
#include "Mesh.h"

class Mesh;
class Skeleton;
class Material;
struct aiScene;

struct IndexRange
{
  //the offset to the 0th index for this mesh
  int firstIndexOffset;  
  //the first index of the vertex element in the vertex buffer range
  int firstVertex;
  //the number of elements in that range
  int indexCount;
};

class Model
{
public:

  Model();
  Model(const string& name, const string& filename);

  int GetMeshCount() const;
  std::vector<vec3> const& GetVertices() const;
  std::vector<vec3> const& GetNormals() const;
  std::vector<vec2> const& GetTexCoords() const;
  std::vector<vec4> const& GetVertexColours() const;
  std::vector<int> const& GetIndices() const;
  std::vector<VertexBoneIDs> const& GetBoneIDs() const;
  std::vector<VertexBoneWeights> const& GetBoneWeights() const;
  std::vector<mat4> GetBoneTransforms(int animationIndex, float time);

  IndexRange const& GetMeshIndexRange(int meshIndex) const;
  Material const& GetMeshMaterial(int meshIndex) const;
  string GetMeshTextureName(int meshIndex, TextureType const& type) const;
  

private: 
	string m_name;
  std::vector<Mesh*> m_meshes;
  std::vector<IndexRange> m_meshIndexRanges;
  std::vector<Material*> m_materials;
  Skeleton* pSkeleton;

  std::vector<vec3> m_vertices;
  std::vector<vec3> m_normals;
  std::vector<vec2> m_texCoords;
  std::vector<vec4> m_vertexColours;
  std::vector<int> m_indices;
  std::vector<VertexBoneIDs> m_boneIDs;
  std::vector<VertexBoneWeights> m_boneWeights;

  void LoadAssimpMaterials(const aiScene* pScene);
  void LoadAssimpSkeleton(const aiScene* pScene);
  void LoadAssimpMeshes(const aiScene* pScene);
  void LoadVertexAttributes();

};
#endif // Model_h__