#include "Animation.h"
#include "assimp/anim.h"


Animation::Animation(aiAnimation const* pAnimation, Bimap<string, int> const& boneLookup)
{
  m_name = pAnimation->mName.data;
  m_duration = float(pAnimation->mDuration);
  m_ticksPerSecond = float(pAnimation->mTicksPerSecond);
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
  return m_boneKeyFrames.at(boneID);
}

mat4 Animation::GetBoneTransform(int boneID, float time) const
{
  return m_boneKeyFrames.at(boneID)->GetTransform(fmod(time * m_ticksPerSecond, m_duration));
}

bool Animation::HasBoneTransform(int boneID) const
{
	return m_boneKeyFrames.find(boneID) != m_boneKeyFrames.end();
}

void Animation::LoadKeyFrames(aiAnimation const* pAnimation, Bimap<string, int> const& boneLookup)
{
	for (uint i = 0; i < pAnimation->mNumChannels; i++)
	{
		int boneIndex = boneLookup.GetValue(pAnimation->mChannels[i]->mNodeName.data);
		m_boneKeyFrames.emplace(boneIndex, new BoneKeySequence(pAnimation->mChannels[i], boneIndex));
	}

}
