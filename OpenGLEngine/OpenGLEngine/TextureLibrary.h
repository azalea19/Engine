#ifndef TextureLibrary_h__
#define TextureLibrary_h__

#include <unordered_map>
#include "Gl/glew.h"
#include "Types.h"
#include "Singleton.h"

class TextureLibrary : public Singleton<TextureLibrary>
{

public:

	void initTextureLibrary();

	void AddTexture(string name, GLuint textureID);

	void AddTexture(string name, string filePath);

	GLuint GetTexture(string name);

private:

	std::unordered_map<string, GLuint> textures;

};


#endif