#ifndef Model_h__
#define Model_h__

#include "Types.h"
#include <unordered_map>
#include "Mesh.h"
#include "IAnimated.h"
#include "IMeshCollection.h"


/**
* @file Model.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief The model stores all of the data needed to create a model object. 
* It contains all of the data but no methods for rendering itself.
*
*/

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

  /// <summary>
  /// Initializes a new instance of the <see cref="Model"/> class.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <param name="filename">The filename.</param>
  Model(const string& name, const string& filename);
  
  /// <summary>
  /// Gets the texture coords.
  /// </summary>
  /// <param name="type">The type.</param>
  /// <returns>std::vector<vec2></returns>
  std::vector<vec2> const& GetTexCoords(TextureType type) const;

  /// <summary>
  /// Gets the vertex colours.
  /// </summary>
  /// <returns>std::vector<vec4></returns>
  std::vector<vec4> const& GetVertexColours() const;

  /// <summary>
  /// Gets the bone IDs.
  /// </summary>
  /// <returns>std::vector<VertexBoneIDs></returns>
  std::vector<VertexBoneIDs> const& GetBoneIDs() const;

  /// <summary>
  /// Gets the bone weights.
  /// </summary>
  /// <returns>std::vector<VertexBoneWeights></returns>
  std::vector<VertexBoneWeights> const& GetBoneWeights() const;

  /// <summary>
  /// Gets the bone transforms.
  /// </summary>
  /// <param name="animationIndex">Index of the animation.</param>
  /// <param name="time">The time.</param>
  /// <returns>std::vector<mat4></returns>
  std::vector<mat4> GetBoneTransforms(int animationIndex, float time);

  /// <summary>
  /// Gets the mesh index range.
  /// </summary>
  /// <param name="meshIndex">Index of the mesh.</param>
  /// <returns>IndexRange</returns>
  IndexRange const& GetMeshIndexRange(int meshIndex) const;

  /// <summary>
  /// Gets the mesh material.
  /// </summary>
  /// <param name="meshIndex">Index of the mesh.</param>
  /// <returns>Material</returns>
  Material const& GetMeshMaterial(int meshIndex) const;

  /// <summary>
  /// Gets the name of the mesh texture.
  /// </summary>
  /// <param name="meshIndex">Index of the mesh.</param>
  /// <param name="type">The type.</param>
  /// <returns>string</returns>
  string GetMeshTextureName(int meshIndex, TextureType const& type) const;

  /// <summary>
  /// Determines whether this instance has animation.
  /// </summary>
  /// <returns>
  ///   <c>true</c> if this instance has animation; otherwise, <c>false</c>.
  /// </returns>
  bool HasAnimation() const;

  /// <summary>
  /// Gets the animation count.
  /// </summary>
  /// <returns>int</returns>
  virtual int GetAnimationCount() const override;

  /// <summary>
  /// Gets the index of the animation.
  /// </summary>
  /// <param name="animationName">Name of the animation.</param>
  /// <returns>int</returns>
  virtual int GetAnimationIndex(string const& animationName) const override;

  /// <summary>
  /// Gets the name of the animation.
  /// </summary>
  /// <param name="animationIndex">Index of the animation.</param>
  /// <returns>string</returns>
  virtual string const& GetAnimationName(int animationIndex) const override;


  /// <summary>
  /// Gets the mesh.
  /// </summary>
  /// <param name="meshIndex">Index of the mesh.</param>
  /// <returns>IMesh</returns>
  virtual IMesh const& GetMesh(int meshIndex) const override;

  /// <summary>
  /// Gets the mesh count.
  /// </summary>
  /// <returns>int</returns>
  virtual int GetMeshCount() const override;

  Skeleton const* GetSkeleton() const;

private:

  /// <summary>
  /// The name
  /// </summary>
  string m_name;

  /// <summary>
  /// The meshes
  /// </summary>
  std::vector<Mesh*> m_meshes;

  /// <summary>
  /// The mesh index ranges
  /// </summary>
  std::vector<IndexRange> m_meshIndexRanges;

  /// <summary>
  /// The materials
  /// </summary>
  std::vector<Material*> m_materials;

  /// <summary>
  /// The skeleton
  /// </summary>
  Skeleton* pSkeleton;

  /// <summary>
  /// The m texture coords
  /// </summary>
  std::vector<vec2> m_texCoords[2];

  /// <summary>
  /// The m vertex colours
  /// </summary>
  std::vector<vec4> m_vertexColours;

  /// <summary>
  /// The m bone IDs
  /// </summary>
  std::vector<VertexBoneIDs> m_boneIDs;

  /// <summary>
  /// The bone weights
  /// </summary>
  std::vector<VertexBoneWeights> m_boneWeights;

  /// <summary>
  /// Whether model has animation
  /// </summary>
  bool m_hasAnimation;

  /// <summary>
  /// Loads the assimp materials.
  /// </summary>
  /// <param name="pScene">The p scene.</param>
  /// <param name="modelDir">The model dir.</param>
  void LoadAssimpMaterials(const aiScene* pScene, string const& modelDir);

  /// <summary>
  /// Loads the assimp skeleton.
  /// </summary>
  /// <param name="pScene">The p scene.</param>
  void LoadAssimpSkeleton(const aiScene* pScene);
  
  /// <summary>
  /// Loads the assimp meshes.
  /// </summary>
  /// <param name="pScene">The p scene.</param>
  void LoadAssimpMeshes(const aiScene* pScene);
  
  /// <summary>
  /// Loads the vertex attributes.
  /// </summary>
  void LoadVertexAttributes();

};
#endif // Model_h__