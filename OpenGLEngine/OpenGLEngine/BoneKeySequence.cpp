#include "BoneKeySequence.h"
#include "MMath.h"
#include "assimp/anim.h"
#include "AssimpToGLM.h"

BoneKeySequence::BoneKeySequence(aiNodeAnim const* pAnim, int boneID)
  : m_boneID(boneID)
{
  LoadPositionKeys(pAnim);
  LoadRotationKeys(pAnim);
  LoadScaleKeys(pAnim);
}

int BoneKeySequence::GetBoneID() const
{
  return m_boneID;
}

vec3 BoneKeySequence::GetPosition(float time) const
{
  if (time <= m_positionKeys[0].time)
    return m_positionKeys[0].position;

  if (time >= m_positionKeys[m_positionKeys.size() - 1].time)
    return m_positionKeys[m_positionKeys.size() - 1].position;

  //Find last frame before the current time
  int lastFrameIndex = 0;
  for (int i = 1; i < m_positionKeys.size(); i++)
    if (m_positionKeys[i].time < time)
      lastFrameIndex = i;
    else
      break;

  PositionKey const& lastKey = m_positionKeys[lastFrameIndex];
  PositionKey const& nextKey = m_positionKeys[lastFrameIndex + 1];
  
  float timeSinceLast = time - lastKey.time;
  float timeBetweenFrames = nextKey.time - lastKey.time;
  float interpolationFactor = timeSinceLast / timeBetweenFrames;
  interpolationFactor = mClamp(interpolationFactor, 0, 1);
  
  return glm::lerp(lastKey.position, nextKey.position, interpolationFactor);
}

quat BoneKeySequence::GetRotation(float time) const
{
  if (time <= m_rotationKeys[0].time)
    return m_rotationKeys[0].rotation;

  if (time >= m_rotationKeys[m_rotationKeys.size() - 1].time)
    return m_rotationKeys[m_rotationKeys.size() - 1].rotation;

  //Find last frame before the current time
  int lastFrameIndex = 0;
  for (int i = 1; i < m_rotationKeys.size(); i++)
    if (m_rotationKeys[i].time < time)
      lastFrameIndex = i;
    else
      break;

  RotationKey const& lastKey = m_rotationKeys[lastFrameIndex];
  RotationKey const& nextKey = m_rotationKeys[lastFrameIndex + 1];

  float timeSinceLast = time - lastKey.time;
  float timeBetweenFrames = nextKey.time - lastKey.time;
  float interpolationFactor = timeSinceLast / timeBetweenFrames;
  interpolationFactor = mClamp(interpolationFactor, 0, 1);

  return glm::lerp(lastKey.rotation, nextKey.rotation, interpolationFactor);
}

vec3 BoneKeySequence::GetScale(float time) const
{
  if (time <= m_scaleKeys[0].time)
    return m_scaleKeys[0].scale;

  if (time >= m_scaleKeys[m_scaleKeys.size() - 1].time)
    return m_scaleKeys[m_scaleKeys.size() - 1].scale;

  //Find last frame before the current time
  int lastFrameIndex = 0;
  for (int i = 1; i < m_scaleKeys.size(); i++)
    if (m_scaleKeys[i].time < time)
      lastFrameIndex = i;
    else
      break;

  ScaleKey const& lastKey = m_scaleKeys[lastFrameIndex];
  ScaleKey const& nextKey = m_scaleKeys[lastFrameIndex + 1];

  float timeSinceLast = time - lastKey.time;
  float timeBetweenFrames = nextKey.time - lastKey.time;
  float interpolationFactor = timeSinceLast / timeBetweenFrames;
  interpolationFactor = mClamp(interpolationFactor, 0, 1);

  return glm::lerp(lastKey.scale, nextKey.scale, interpolationFactor);
}

mat4 BoneKeySequence::GetTransform(float time) const
{
  vec3 position = GetPosition(time);
  vec3 scale = GetScale(time);
  quat rotation = GetRotation(time);

  mat4 translationMatrix = glm::translate(position);
  mat4 scalingMatrix = glm::scale(scale);
  mat4 rotationMatrix = mat4(rotation);

  return translationMatrix * rotationMatrix * scalingMatrix;
}

void BoneKeySequence::LoadPositionKeys(aiNodeAnim const* pAnim)
{
  for (uint i = 0; i < pAnim->mNumPositionKeys; i++)
	  m_positionKeys.push_back(PositionKey{ float(pAnim->mPositionKeys[i].mTime), ASToGLM(pAnim->mPositionKeys[i].mValue) });
}

void BoneKeySequence::LoadRotationKeys(aiNodeAnim const* pAnim)
{
  for (uint i = 0; i < pAnim->mNumRotationKeys; i++)
	  m_rotationKeys.push_back(RotationKey{ float(pAnim->mRotationKeys[i].mTime), ASToGLM(pAnim->mRotationKeys[i].mValue) });
}

void BoneKeySequence::LoadScaleKeys(aiNodeAnim const* pAnim)
{
  for (uint i = 0; i < pAnim->mNumScalingKeys; i++)
	  m_scaleKeys.push_back(ScaleKey{ float(pAnim->mScalingKeys[i].mTime), ASToGLM(pAnim->mScalingKeys[i].mValue) });
}