#include "Material.h"
#include "assimp/material.h"
#include "TextureLibrary.h"



Material::Material(string name, const aiMaterial* pMaterial, string const& modelDir)
{
  this->name = name;
  if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
  {
    aiString path;
    pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path);

    string texName = name + "_diffuse";
    TextureLibrary::GetInstance().AddTexture(texName, modelDir + string(path.data));
    m_textures.emplace(TT_Diffuse, texName);
  }
  if (pMaterial->GetTextureCount(aiTextureType_OPACITY) > 0)
  {
    aiString path;
    pMaterial->GetTexture(aiTextureType_OPACITY, 0, &path);

    string texName = name + "_alpha";
    TextureLibrary::GetInstance().AddTexture(texName, modelDir + string(path.data), false);
    m_textures.emplace(TT_Alpha, texName);
  }
}

string Material::GetTextureName(TextureType const& type) const
{
	auto got = m_textures.find(type);
	if (got == m_textures.end())
	{
		return "Texture not supplied.";
	}
	else
	{
		return got->second;
	}

}
