#ifndef BoneKeySequence_h__
#define BoneKeySequence_h__

#include "Types.h"


/** 
* @file BoneKeySequence.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief Contains the data relating to a key frame of the animation.
* Such as the new position, rotation and scale.
*/


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
  
  /// <summary>
  /// Initializes a new instance of the <see cref="BoneKeySequence"/> class.
  /// </summary>
  /// <param name="pAnim">The p anim.</param>
  /// <param name="boneID">The bone identifier.</param>
  BoneKeySequence(aiNodeAnim const* pAnim, int boneID);
  
  /// <summary>
  /// Gets the bone identifier.
  /// </summary>
  /// <returns>int</returns>
  int GetBoneID() const;
  

  /// <summary>
  /// Gets the position.
  /// </summary>
  /// <param name="time">The time.</param>
  /// <returns>vec3</returns>
  vec3 GetPosition(float time) const;
  
  /// <summary>
  /// Gets the rotation.
  /// </summary>
  /// <param name="time">The time.</param>
  /// <returns>quat</returns>
  quat GetRotation(float time) const;
  
  /// <summary>
  /// Gets the scale.
  /// </summary>
  /// <param name="time">The time.</param>
  /// <returns>vec3</returns>
  vec3 GetScale(float time) const;
  
  /// <summary>
  /// Gets the transform.
  /// </summary>
  /// <param name="time">The time.</param>
  /// <returns>mat4</returns>
  mat4 GetTransform(float time) const;

private:

  /// <summary>
  /// The bone identifier
  /// </summary>
  int m_boneID;

  /// <summary>
  /// The position keys
  /// </summary>
  std::vector<PositionKey> m_positionKeys;

  /// <summary>
  /// The rotation keys
  /// </summary>
  std::vector<RotationKey> m_rotationKeys;

  /// <summary>
  /// The scale keys
  /// </summary>
  std::vector<ScaleKey> m_scaleKeys;

  /// <summary>
  /// Loads the position keys.
  /// </summary>
  /// <param name="pAnim">The p anim.</param>
  void LoadPositionKeys(aiNodeAnim const* pAnim);

  /// <summary>
  /// Loads the rotation keys.
  /// </summary>
  /// <param name="pAnim">The p anim.</param>
  void LoadRotationKeys(aiNodeAnim const* pAnim);

  /// <summary>
  /// Loads the scale keys.
  /// </summary>
  /// <param name="pAnim">The p anim.</param>
  void LoadScaleKeys(aiNodeAnim const* pAnim);

};

#endif