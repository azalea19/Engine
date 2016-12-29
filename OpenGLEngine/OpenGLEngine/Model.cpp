#include "Model.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Material.h"
#include "Skeleton.h"
#include "Mesh.h"
#include "Utility.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals /*| aiProcess_FlipUVs*/ | aiProcess_JoinIdenticalVertices | aiProcess_LimitBoneWeights )


Model::Model(const string& name, const string& filename)
  : m_name(name)
  , pSkeleton(nullptr)
{
  Assimp::Importer im;
  const aiScene* pScene = im.ReadFile(filename,ASSIMP_LOAD_FLAGS);
  LoadAssimpMaterials(pScene, GetDirectoryFromFileName(filename));
  LoadAssimpSkeleton(pScene);
  LoadAssimpMeshes(pScene);
  LoadVertexAttributes();
}

void Model::LoadAssimpMaterials(const aiScene* pScene, string const& modelDir)
{
  char materialName[1024];
  for (uint i = 0; i < pScene->mNumMaterials; i++)
  {
    sprintf_s(materialName, "%s_Material%d", m_name.c_str(), i);
    m_materials.push_back(new Material(materialName, pScene->mMaterials[i], modelDir));
  }
}

void Model::LoadAssimpSkeleton(const aiScene* pScene)
{
  if (pScene->HasAnimations())
  {
    m_hasAnimation = true;
    pSkeleton = new Skeleton(pScene);
  }
  else
  {
    m_hasAnimation = false;
  }
}

void Model::LoadAssimpMeshes(const aiScene* pScene)
{
  for (uint i = 0; i < pScene->mNumMeshes; i++)
  {
    m_meshes.push_back(new Mesh(pScene->mMeshes[i], pSkeleton->GetBoneLookup()));
  }
}

void Model::LoadVertexAttributes()
{
  int indexCount = 0;
  int vertexCount = 0;
  for (int i = 0; i < m_meshes.size(); i++)
  {
    const Mesh& mesh = *(m_meshes[i]);

    m_meshIndexRanges.push_back(IndexRange{ indexCount, vertexCount, int(mesh.GetIndexCount()) });

    VectorConcatenate(m_texCoords[TT_Diffuse], mesh.GetTexCoords(TT_Diffuse));
    VectorConcatenate(m_texCoords[TT_Alpha], mesh.GetTexCoords(TT_Alpha));
    VectorConcatenate(m_vertexColours, mesh.GetVertexColours());
    VectorConcatenate(m_boneIDs, mesh.GetBoneIDs());
    VectorConcatenate(m_boneWeights, mesh.GetBoneWeights());

    indexCount += mesh.GetIndexCount();
    vertexCount += mesh.GetVertexCount();
  }
}


std::vector<vec2> const& Model::GetTexCoords(TextureType type) const
{
  return m_texCoords[type];
}

std::vector<vec4> const& Model::GetVertexColours() const
{
  return m_vertexColours;
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

int Model::GetAnimationCount() const
{
  if (pSkeleton)
    return pSkeleton->GetAnimationCount();
  else
    return 0;
}

int Model::GetAnimationIndex(string const& animationName) const
{
  return pSkeleton->GetAnimationIndex(animationName);
}

string const& Model::GetAnimationName(int animationIndex) const
{
  return pSkeleton->GetAnimationName(animationIndex);
}

IMesh const& Model::GetMesh(int meshIndex) const
{
  return *(m_meshes[meshIndex]);
}

int Model::GetMeshCount() const
{
  return int(m_meshes.size());
}

bool Model::HasAnimation() const
{
  return m_hasAnimation;
}
