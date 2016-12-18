#include "Material.h"
#include "assimp/material.h"
#include "TextureLibrary.h"



Material::Material(string name, const aiMaterial* pMaterial)
{
  this->name = name;
  if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
  {
    aiString path;
    pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path);

    string texName = name + "_diffuse";
    TextureLibrary::GetInstance().AddTexture(texName, path.data);
    m_textures.emplace(TT_Diffuse, texName);
  }
}

string const& Material::GetTextureName(TextureType const& type) const
{
  return m_textures.at(type);
}
