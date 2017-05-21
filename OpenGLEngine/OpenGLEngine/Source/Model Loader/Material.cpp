#include "Material.h"
#include "assimp/material.h"
#include "TextureLibrary.h"



Material::Material(string name, const aiMaterial* pMaterial, string const& modelDir)
{
  this->name = name;

  if (name == "Terrain_Material1")
  {
    diffuseTextureCount = pMaterial->GetTextureCount(aiTextureType_DIFFUSE);

    for (int i = 0; i < diffuseTextureCount; i++)
    {
      aiString path;
      pMaterial->GetTexture(aiTextureType_DIFFUSE, i, &path);

      string texName = name + "_diffuse" + std::to_string(i);
      TextureLibrary::GetInstance().AddTexture(texName, modelDir + string(path.data));
      m_textures.emplace(TextureType(TT_Diffuse0 + i), texName);
    }
    if (pMaterial->GetTextureCount(aiTextureType_SPECULAR) > 0)
    {
      aiString path;
      pMaterial->GetTexture(aiTextureType_SPECULAR, 0, &path);

      string texName = name + "_diffuse" + std::to_string(diffuseTextureCount);
      TextureLibrary::GetInstance().AddTexture(texName, modelDir + string(path.data));
      m_textures.emplace(TextureType(TT_Diffuse0 + diffuseTextureCount), texName);

      diffuseTextureCount++;
    }
    if (pMaterial->GetTextureCount(aiTextureType_AMBIENT) > 0)
    {
      aiString path;
      pMaterial->GetTexture(aiTextureType_AMBIENT, 0, &path);

      string texName = name + "_diffuse" + std::to_string(diffuseTextureCount);
      TextureLibrary::GetInstance().AddTexture(texName, modelDir + string(path.data));
      m_textures.emplace(TextureType(TT_Diffuse0 + diffuseTextureCount), texName);

      diffuseTextureCount++;

    }
    if (pMaterial->GetTextureCount(aiTextureType_HEIGHT))
    {
      aiString path;
      pMaterial->GetTexture(aiTextureType_HEIGHT, 0, &path);

      string texName = name + "_diffuse" + std::to_string(diffuseTextureCount);
      TextureLibrary::GetInstance().AddTexture(texName, modelDir + string(path.data));
      m_textures.emplace(TextureType(TT_Diffuse0 + diffuseTextureCount), texName);

      diffuseTextureCount++;
    }
  }
  else
  {
    if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {
      diffuseTextureCount = 1;
      aiString path;
      pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path);

      string texName = name + "_diffuse" + std::to_string(0);
      TextureLibrary::GetInstance().AddTexture(texName, modelDir + string(path.data));
      m_textures.emplace(TextureType(TT_Diffuse0), texName);
    }
    else
    {
      diffuseTextureCount = 0;
    }
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

uint Material::GetDiffuseTextureCount() const
{
  return diffuseTextureCount;
}
