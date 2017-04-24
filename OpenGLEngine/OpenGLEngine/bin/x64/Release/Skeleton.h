#ifndef Skeleton_h__
#define Skeleton_h__

#include "Types.h"
#include "Bimap.h"
#include "IAnimated.h"
#include <memory>

/**
* @file Skeleton.h
* @Author Maddisen Topaz
* @date   S2, 2017
* @brief The skeleton of the model (its bones) and its animations.
* Each bone has an ID and each child bone of this bone is identified by this ID. 
* A parent bone may have a maximum of 4 children. Thus a bone may only be influenced by up to four bones it is connected to.
*/


class Animation;
struct aiScene;
struct aiNode;

struct Bone
{
  int m_ID;
  std::vector<int> m_childBoneIDs;
  mat4 transform;
  mat4 offsetMatrix;
};

class Skeleton : public IAnimated
{
public:

  /// <summary>
  /// Initializes a new instance of the <see cref="Skeleton"/> class.
  /// Uses the Assimp library.
  /// For more information on the Assimp aiScene data structure
  /// See: http://www.assimp.org/lib_html/structai_scene.html
  /// </summary>
  /// <param name="pScene">The pointer to the scene.</param>
  Skeleton(aiScene const* pScene);

  /// <summary>
  /// Gets the bone transforms.
  /// </summary>
  /// <param name="animationIndex">Index of the animation.</param>
  /// <param name="time">The time.</param>
  /// <returns>std::vector<mat4></returns>
  std::vector<mat4> GetBoneTransforms(int animationIndex, float time) const;

  /// <summary>
  /// Gets the bone transforms.
  /// </summary>
  /// <param name="animationName">Name of the animation.</param>
  /// <param name="time">The time.</param>
  /// <returns>std::vector<mat4></returns>
  std::vector<mat4> GetBoneTransforms(string const& animationName, float time) const;
  
  /// <summary>
  /// Gets the bone lookup.
  /// </summary>
  /// <returns> A reference to the bone lookup Bimap. Bimap<string,int> </returns>
  Bimap<string, int> const& GetBoneLookup() const;

  /// <summary>
  /// Gets the animation count.
  /// </summary>
  /// <returns>int</returns>
  virtual int GetAnimationCount() const override;

  /// <summary>
  /// Gets the index of the animation.
  /// </summary>
  /// <param name="animationName">Name of the animation.</param>
  /// <returns>int</returns>
  virtual int GetAnimationIndex(string const& animationName) const override;

  /// <summary>
  /// Gets the name of the animation.
  /// </summary>
  /// <param name="animationIndex">Index of the animation.</param>
  /// <returns>string</returns>
  virtual string const& GetAnimationName(int animationIndex) const override;

private:

  /// <summary>
  /// The bones
  /// </summary>
  std::vector<Bone> m_bones;

  /// <summary>
  /// The animations
  /// </summary>
  std::vector<std::unique_ptr<Animation>> m_animations;

  /// <summary>
  /// The bone lookup
  /// </summary>
  Bimap<string, int> m_boneLookup;

  /// <summary>
  /// The animation lookup
  /// </summary>
  Bimap<string, int> m_animationLookup;

  /// <summary>
  /// The global inverse transform
  /// </summary>
  mat4 m_globalInverseTransform;

  /// <summary>
  /// Calculates the bone transforms.
  /// </summary>
  /// <param name="animationIndex">Index of the animation.</param>
  /// <param name="time">The time.</param>
  /// <param name="finalTransforms">The final transforms.</param>
  /// <param name="parentTransform">The parent transform.</param>
  /// <param name="boneIndex">Index of the bone.</param>
  void CalculateBoneTransforms(int animationIndex, float time, std::vector<mat4> &finalTransforms, mat4 parentTransform = mat4(), int boneIndex = 0) const;
  
  /// <summary>
  /// Creates the bone lookup.
  /// </summary>
  /// <param name="pNode">The p node.</param>
  void CreateBoneLookup(aiNode const* pNode);
  
  /// <summary>
  /// Loads the bones.
  /// </summary>
  /// <param name="pScene">The pointer to the scene.</param>
  void LoadBones(aiScene const* pScene);
  
  /// <summary>
  /// Loads the animations.
  /// </summary>
  /// <param name="pScene">The pointer to the scene.</param>
  void LoadAnimations(aiScene const* pScene);

};

#endif