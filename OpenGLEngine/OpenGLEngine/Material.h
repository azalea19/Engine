#ifndef Material_h__
#define Material_h__

#include "Types.h"
#include <unordered_map>

enum TextureType
{
  TT_Diffuse,
  TT_Alpha,
  TT_TextureTypeCount,
};

struct aiMaterial;

class Material
{
public:
  Material(string name, const aiMaterial* pMaterial, string const& modelDir);
  string GetTextureName(TextureType const& type) const;

private:
  string name;
  std::unordered_map<TextureType, string> m_textures;
};
#endif // Material_h__