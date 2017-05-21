#ifndef Material_h__
#define Material_h__

#include "Types.h"
#include <unordered_map>



/**
* @file Material.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief
*
*/

enum TextureType
{
  TT_Alpha,
  //TT_TextureTypeCount,
  TT_Diffuse0,
};

struct aiMaterial;

class Material
{
public:
  
  /// <summary>
  /// Initializes a new instance of the <see cref="Material"/> class.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <param name="pMaterial">The p material.</param>
  /// <param name="modelDir">The model dir.</param>
  Material(string name, const aiMaterial* pMaterial, string const& modelDir);
  
  /// <summary>
  /// Gets the name of the texture.
  /// </summary>
  /// <param name="type">The type.</param>
  /// <returns></returns>
  string GetTextureName(TextureType const& type) const;

  uint GetDiffuseTextureCount() const;

private:

  /// <summary>
  /// The name
  /// </summary>
  string name;

  uint diffuseTextureCount;
  
  /// <summary>
  /// The textures
  /// </summary>
  std::unordered_map<TextureType, string> m_textures;
};
#endif // Material_h__