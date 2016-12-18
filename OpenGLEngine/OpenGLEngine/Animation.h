#ifndef Animation_h__
#define Animation_h__

#include "Types.h"
#include "BoneKeySequence.h"
#include "Bimap.h"

struct aiAnimation;

class Animation
{

public:
  Animation(aiAnimation const* pAnimation, Bimap<string, int> const& boneLookup);
  string const& GetName() const;
  float GetDuration() const;
  float GetTicksPerSecond() const;
  BoneKeySequence* const& GetBoneKeySequence(int boneID) const;
  mat4 GetBoneTransform(int boneID, float time) const;
  bool HasBoneTransform(int boneID) const;

private:
  string m_name;
  float m_duration;
  float m_ticksPerSecond;
  std::unordered_map<int, BoneKeySequence*> m_boneKeyFrames;

  void LoadKeyFrames(aiAnimation const* pAnimation, Bimap<string, int> const& boneLookup);
  
};
#endif // Animation_h__