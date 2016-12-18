#ifndef BoneKeySequence_h__
#define BoneKeySequence_h__

#include "Types.h"
#include "Bimap.h"

struct PositionKey
{
  float time;
  vec3 position;
};

struct RotationKey
{
  float time;
  quat rotation;
};

struct ScaleKey
{
  float time;
  vec3 scale;
};

struct aiNodeAnim;

class BoneKeySequence
{
public:
  BoneKeySequence(aiNodeAnim const* pAnim, int boneID);
  int GetBoneID() const;
  vec3 GetPosition(float time) const;
  quat GetRotation(float time) const;
  vec3 GetScale(float time) const;
  mat4 GetTransform(float time) const;

private:
  int m_boneID;
  std::vector<PositionKey> m_positionKeys;
  std::vector<RotationKey> m_rotationKeys;
  std::vector<ScaleKey> m_scaleKeys;

  void LoadPositionKeys(aiNodeAnim const* pAnim);
  void LoadRotationKeys(aiNodeAnim const* pAnim);
  void LoadScaleKeys(aiNodeAnim const* pAnim);
};

#endif