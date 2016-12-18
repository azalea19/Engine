#include "NewModel.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Material.h"
#include "Skeleton.h"
#include "NewMesh.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_LimitBoneWeights )


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
    Mesh *pMesh = new Mesh(pScene->mMeshes[i], pSkeleton->GetBoneLookup());
  }
}



