#include "TextureLibrary.h"
#include "Texture.h"

#define NOT_FOUND GLuint(-1)

void TextureLibrary::InitTextureLibrary()
{
	GetInstance().AddTexture("Error", "Error_Texture.jpg");
}

void TextureLibrary::AddTexture(string const& name, GLuint textureID)
{
	textures.emplace(name, textureID);
}

void TextureLibrary::AddTexture(string const& name, string const& filePath, bool useMips)
{
	GLuint textureID = LoadImage(filePath.c_str(), useMips);
	AddTexture(name, textureID);

}

GLuint TextureLibrary::GetTexture(string const& name) const
{
	std::unordered_map<string, GLuint>::const_iterator got = textures.find(name);
	if (got == textures.end())
	{
		printf("Texture with name %s not found.", name.c_str());
		return NOT_FOUND;
	}
	else
		return got->second;
}
