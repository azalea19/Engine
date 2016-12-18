#include "Animation.h"
#include "assimp/anim.h"


Animation::Animation(aiAnimation const* pAnimation, Bimap<string, int> const& boneLookup)
{
  m_name = pAnimation->mName.data;
  m_duration = pAnimation->mDuration;
  m_ticksPerSecond = pAnimation->mTicksPerSecond;
  LoadKeyFrames(pAnimation, boneLookup);
}

string const& Animation::GetName() const
{
  return m_name;
}

float Animation::GetDuration() const
{
  return m_duration;
}

float Animation::GetTicksPerSecond() const
{
  return m_ticksPerSecond;
}

BoneKeySequence* const& Animation::GetBoneKeySequence(int boneID) const
{
  return m_boneKeyFrames[boneID];
}

mat4 Animation::GetBoneTransform(int boneID, float time) const
{
  return m_boneKeyFrames[boneID]->GetTransform(time);
}

void Animation::LoadKeyFrames(aiAnimation const* pAnimation, Bimap<string, int> const& boneLookup)
{
  for (int i = 0; i < pAnimation->mNumChannels; i++)
    m_boneKeyFrames.push_back(new BoneKeySequence(pAnimation->mChannels[i], boneLookup));
}
