#include "Types.h"
#include <unordered_map>

enum TextureType
{
  TT_Diffuse,
  TT_TextureTypeCount,
};

class aiMaterial;

class Material
{
public:
  Material(string name, const aiMaterial* pMaterial);

private:
  string name;
  std::unordered_map<TextureType, string> m_textures;
};