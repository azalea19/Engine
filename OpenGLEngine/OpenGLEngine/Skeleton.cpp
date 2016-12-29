#include "Skeleton.h"
#include "Animation.h"
#include "assimp/scene.h"
#include "AssimpToGLM.h"

Skeleton::Skeleton(const aiScene* pScene)
{
  m_globalInverseTransform = glm::inverse(ASToGLM(pScene->mRootNode->mTransformation));
  LoadBones(pScene);
  LoadAnimations(pScene);
}

std::vector<mat4> Skeleton::GetBoneTransforms(int animationIndex, float time) const
{
  std::vector<mat4> finalTransforms;
  finalTransforms.resize(m_bones.size());
  if(animationIndex >= 0)
    CalculateBoneTransforms(animationIndex, time, finalTransforms);
  return finalTransforms;
}

std::vector<mat4> Skeleton::GetBoneTransforms(string animationName, float time) const
{
  int animationIndex = m_animationLookup.GetValue(animationName);
  std::vector<mat4> finalTransforms;
  CalculateBoneTransforms(animationIndex, time, finalTransforms);
  return finalTransforms;
}

void Skeleton::CalculateBoneTransforms(int animationIndex, float time, std::vector<mat4> &finalTransforms, mat4 parentTransform, int boneIndex) const
{
  const Bone& bone = m_bones[boneIndex];
  const Animation* pAnimation = m_animations[animationIndex];

  mat4 boneTransform = bone.transform;
  if (pAnimation && pAnimation->HasBoneTransform(boneIndex))
    boneTransform = pAnimation->GetBoneTransform(boneIndex, time);

  mat4 globalTransform = parentTransform * boneTransform;
  finalTransforms[boneIndex] = m_globalInverseTransform * globalTransform * m_bones[boneIndex].offsetMatrix;

  for (int i = 0; i < m_bones[boneIndex].m_childBoneIDs.size(); i++)
    CalculateBoneTransforms(animationIndex, time, finalTransforms, globalTransform, m_bones[boneIndex].m_childBoneIDs[i]);
}

void Skeleton::CreateBoneLookup(const aiNode* pNode)
{
  int boneIndex = m_boneLookup.Count();
  string boneName = pNode->mName.data;
  if (!m_boneLookup.HasKey(boneName))
  {

    m_boneLookup.Add(pNode->mName.data, boneIndex);
    m_bones.emplace_back();
    m_bones[boneIndex].m_ID = boneIndex;
    m_bones[boneIndex].transform = ASToGLM(pNode->mTransformation);
    for (uint i = 0; i < pNode->mNumChildren; i++)
    {
      CreateBoneLookup(pNode->mChildren[i]);
      m_bones[boneIndex].m_childBoneIDs.push_back(m_boneLookup.GetValue(pNode->mChildren[i]->mName.data));
    }
  }


}

void Skeleton::LoadBones(const aiScene* pScene)
{
  CreateBoneLookup(pScene->mRootNode);
  for (uint meshIndex = 0; meshIndex < pScene->mNumMeshes; meshIndex++)
  {
    const aiMesh* m = pScene->mMeshes[meshIndex];
    for (uint b = 0; b < m->mNumBones; b++)
    {
      int boneIndex = m_boneLookup.GetValue(m->mBones[b]->mName.data);
      m_bones[boneIndex].offsetMatrix = ASToGLM(m->mBones[b]->mOffsetMatrix);
    }
  }
}

void Skeleton::LoadAnimations(const aiScene* pScene)
{
  for (uint i = 0; i < pScene->mNumAnimations; i++)
    m_animations.push_back(new Animation(pScene->mAnimations[i], m_boneLookup));

  for (int i = 0; i < m_animations.size(); i++)
    m_animationLookup.Add(m_animations[i]->GetName(), i);
}

Bimap<string, int> const& Skeleton::GetBoneLookup() const
{
  return m_boneLookup;
}

int Skeleton::GetAnimationCount() const
{
  return m_animations.size();
}

int Skeleton::GetAnimationIndex(string const& animationName) const
{
  return m_animationLookup.GetValue(animationName);
}

string const& Skeleton::GetAnimationName(int animationIndex) const
{
  return m_animationLookup.GetKey(animationIndex);
}
