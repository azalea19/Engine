#ifndef Model_h__
#define Model_h__

#include "Types.h"
#include <unordered_map>
#include "Mesh.h"
#include "IAnimated.h"
#include "IMeshCollection.h"

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

class Model : public IAnimated, public IMeshCollection
{
public:

  Model(const string& name, const string& filename);
  
  std::vector<vec2> const& GetTexCoords(TextureType type) const;
  std::vector<vec4> const& GetVertexColours() const;
  std::vector<VertexBoneIDs> const& GetBoneIDs() const;
  std::vector<VertexBoneWeights> const& GetBoneWeights() const;
  std::vector<mat4> GetBoneTransforms(int animationIndex, float time);

  IndexRange const& GetMeshIndexRange(int meshIndex) const;
  Material const& GetMeshMaterial(int meshIndex) const;
  string GetMeshTextureName(int meshIndex, TextureType const& type) const;

  bool HasAnimation() const;
  virtual int GetAnimationCount() const override;
  virtual int GetAnimationIndex(string const& animationName) const override;
  virtual string const& GetAnimationName(int animationIndex) const override;


  virtual IMesh const& GetMesh(int meshIndex) const override;
  virtual int GetMeshCount() const override;

private:
	string m_name;
  std::vector<Mesh*> m_meshes;
  std::vector<IndexRange> m_meshIndexRanges;
  std::vector<Material*> m_materials;
  Skeleton* pSkeleton;

  std::vector<vec2> m_texCoords[TT_TextureTypeCount];
  std::vector<vec4> m_vertexColours;
  std::vector<VertexBoneIDs> m_boneIDs;
  std::vector<VertexBoneWeights> m_boneWeights;

  bool m_hasAnimation;

  void LoadAssimpMaterials(const aiScene* pScene, string const& modelDir);
  void LoadAssimpSkeleton(const aiScene* pScene);
  void LoadAssimpMeshes(const aiScene* pScene);
  void LoadVertexAttributes();

};
#endif // Model_h__