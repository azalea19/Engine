#include "Types.h"
#include "Bimap.h"

class Animation;
class aiScene;
class aiNode;

struct Bone
{
  int m_ID;
  std::vector<int> m_childBoneIDs;
  mat4 transform;
  mat4 offsetMatrix;
};

class Skeleton
{
public:

  Skeleton(const aiScene* pScene);
  std::vector<mat4> GetBoneTransforms(int animationIndex, float time) const;
  std::vector<mat4> GetBoneTransforms(string animationName, float time) const;
  
  Bimap<string, int> const& GetBoneLookup() const;

private:

  std::vector<Bone> m_bones;
  std::vector<Animation*> m_animations;

  Bimap<string, int> m_boneLookup;
  Bimap<string, int> m_animationLookup;

  mat4 m_globalInverseTransform;

  void CalculateBoneTransforms(int animationIndex, float time, std::vector<mat4> &finalTransforms, mat4 parentTransform = mat4(), int boneIndex = 0) const;
  void CreateBoneLookup(const aiNode* pNode);
  void LoadBones(const aiScene* pScene);
  void LoadAnimations(const aiScene* pScene);

};