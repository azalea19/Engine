#include "Model.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Material.h"
#include "Skeleton.h"
#include "Mesh.h"
#include "Utility.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals /*| aiProcess_FlipUVs*/ | aiProcess_JoinIdenticalVertices | aiProcess_LimitBoneWeights )


Model::Model()
{
}

Model::Model(const string& name, const string& filename)
  :m_name(name)
{
  Assimp::Importer im;
  const aiScene* pScene = im.ReadFile(filename,ASSIMP_LOAD_FLAGS);
  LoadAssimpMaterials(pScene);
  LoadAssimpSkeleton(pScene);
  LoadAssimpMeshes(pScene);
  LoadVertexAttributes();
}

void Model::LoadAssimpMaterials(const aiScene* pScene)
{
  char materialName[1024];
  for (int i = 0; i < pScene->mNumMaterials; i++)
  {
    sprintf_s(materialName, "%s_Material%d", m_name.c_str(), i);
    m_materials.push_back(new Material(materialName, pScene->mMaterials[i]));
  }
}

void Model::LoadAssimpSkeleton(const aiScene* pScene)
{
  pSkeleton = new Skeleton(pScene);
}

void Model::LoadAssimpMeshes(const aiScene* pScene)
{
  for (int i = 0; i < pScene->mNumMeshes; i++)
  {
    m_meshes.push_back(new Mesh(pScene->mMeshes[i], pSkeleton->GetBoneLookup()));
  }
}

void Model::LoadVertexAttributes()
{
  for (int i = 0; i < m_meshes.size(); i++)
  {
    std::vector<vec3> const& meshVerts = m_meshes[i]->GetVertices();
    std::vector<vec3> const& meshNorms = m_meshes[i]->GetNormals();
    std::vector<vec2> const& meshTexCoords = m_meshes[i]->GetTexCoords(TT_Diffuse);
    std::vector<vec4> const& meshVertColours = m_meshes[i]->GetVertexColours();
    std::vector<int> const& meshIndices = m_meshes[i]->GetIndices();
    std::vector<VertexBoneIDs> const& meshBoneIDs = m_meshes[i]->GetBoneIDs();
    std::vector<VertexBoneWeights> const& meshBoneWeights = m_meshes[i]->GetBoneWeights();

    m_meshIndexRanges.push_back(IndexRange{ int(m_indices.size()), int(m_vertices.size()), int(meshIndices.size()) });

    VectorConcatenate(m_vertices, meshVerts);
    VectorConcatenate(m_normals, meshNorms);
    VectorConcatenate(m_texCoords, meshTexCoords);
    VectorConcatenate(m_vertexColours, meshVertColours);
    VectorConcatenate(m_indices, meshIndices);
    VectorConcatenate(m_boneIDs, meshBoneIDs);
    VectorConcatenate(m_boneWeights, meshBoneWeights);


  }
}

std::vector<vec3> const& Model::GetVertices() const
{
  return m_vertices;
}

std::vector<vec3> const& Model::GetNormals() const
{
  return m_normals;
}

std::vector<vec2> const& Model::GetTexCoords() const
{
  return m_texCoords;
}

std::vector<vec4> const& Model::GetVertexColours() const
{
  return m_vertexColours;
}

std::vector<int> const& Model::GetIndices() const
{
  return m_indices;
}

std::vector<VertexBoneIDs> const& Model::GetBoneIDs() const
{
  return m_boneIDs;
}

std::vector<VertexBoneWeights> const& Model::GetBoneWeights() const
{
  return m_boneWeights;
}

std::vector<mat4> Model::GetBoneTransforms(int animationIndex, float time)
{
	return pSkeleton->GetBoneTransforms(animationIndex, time);
}

IndexRange const& Model::GetMeshIndexRange(int meshIndex) const
{
  return m_meshIndexRanges[meshIndex];
}

Material const& Model::GetMeshMaterial(int meshIndex) const
{
  int materialIndex = m_meshes[meshIndex]->GetMaterialIndex();
  return *(m_materials[materialIndex]);
}

string Model::GetMeshTextureName(int meshIndex, TextureType const& type) const
{
  return GetMeshMaterial(meshIndex).GetTextureName(type);
}

int Model::GetMeshCount() const
{
  return m_meshes.size();
}