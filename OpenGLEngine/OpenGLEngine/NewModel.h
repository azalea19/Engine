#ifndef Model_h__
#define Model_h__

#include "Types.h"
#include "Texture.h"
#include "TextureLibrary.h"
#include <unordered_map>

class Mesh;
class Skeleton;
class aiMaterial;

class Model
{
public:

  Model();
  Model(const string& name, const string& filename);

private: 
	string m_name;
  std::vector<Mesh*> m_meshes;
  std::vector<Material*> m_materials;
  Skeleton* pSkeleton;

  void LoadAssimpMaterials(const aiScene* pScene);
  void LoadAssimpSkeleton(const aiScene* pScene);
  void LoadAssimpMeshes(const aiScene* pScene);


};
#endif // Model_h__