#ifndef Animation_h__
#define Animation_h__

#include "Types.h"
#include "BoneKeySequence.h"
#include "Bimap.h"
#include <memory>

/**
* @file  Animation.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief  The Animation class contains the data to get back information about an animation.
*
* The animation class is used by the Skeleton class to get back the bone information
* that pertains to a particular animation of the model.
*
*/



struct aiAnimation;


class Animation
{

public:
  
  /// <summary>
  /// Initializes a new instance of the <see cref="Animation"/> class.
  /// </summary>
  /// <param name="pAnimation">The pointer to the animation.</param>
  /// <param name="boneLookup">The bone lookup.</param>
  Animation(aiAnimation const* pAnimation, Bimap<string, int> const& boneLookup);
  
  ~Animation();

  /// <summary>
  /// Gets the name.
  /// </summary>
  /// <returns>string</returns>
  string const& GetName() const;
  
  /// <summary>
  /// Gets the duration.
  /// </summary>
  /// <returns>float</returns>
  float GetDuration() const;
  
  /// <summary>
  /// Gets the ticks per second.
  /// </summary>
  /// <returns>float</returns>
  float GetTicksPerSecond() const;
  
  /// <summary>
  /// Gets the bone key sequence.
  /// </summary>
  /// <param name="boneID">The bone identifier.</param>
  /// <returns>A constant reference to the BoneKeySequence</returns>
  BoneKeySequence const& GetBoneKeySequence(int boneID) const;
  
  /// <summary>
  /// Gets the bone transform.
  /// </summary>
  /// <param name="boneID">The bone identifier.</param>
  /// <param name="time">The time.</param>
  /// <returns>mat4</returns>
  mat4 GetBoneTransform(int boneID, float time) const;
 
  /// <summary>
  /// Determines whether [has bone transform] [the specified bone identifier].
  /// </summary>
  /// <param name="boneID">The bone identifier.</param>
  /// <returns>
  ///   <c>true</c> if [has bone transform] [the specified bone identifier]; otherwise, <c>false</c>.
  /// </returns>
  bool HasBoneTransform(int boneID) const;

private:

  /// <summary>
  /// The name
  /// </summary>
  string m_name;

  /// <summary>
  /// The duration
  /// </summary>
  float m_duration;

  /// <summary>
  /// The ticks per second
  /// </summary>
  float m_ticksPerSecond;

  /// <summary>
  /// The bone key frames.
  /// </summary>
  std::unordered_map<int, std::unique_ptr<BoneKeySequence>> m_boneKeyFrames;


  /// <summary>
  /// Loads the key frames.
  /// </summary>
  /// <param name="pAnimation">The pointer to the animation.</param>
  /// <param name="boneLookup">The bone lookup.</param>
  void LoadKeyFrames(aiAnimation const* pAnimation, Bimap<string, int> const& boneLookup);
  
};
#endif // Animation_h__