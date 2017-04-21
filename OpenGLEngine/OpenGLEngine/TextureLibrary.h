#ifndef TextureLibrary_h__
#define TextureLibrary_h__

#include <unordered_map>
#include "Gl/glew.h"
#include "Types.h"
#include "Singleton.h"

/**
* @file TextureLibrary.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief The texture library contains all of the textures we have access to in the program.
*
*/

class TextureLibrary : public Singleton<TextureLibrary>
{

public:

  /// <summary>
  /// Initializes the texture library.
  /// </summary>
  void InitTextureLibrary();

  /// <summary>
  /// Adds the texture.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <param name="textureID">The texture identifier.</param>
  void AddTexture(string const& name, GLuint textureID);

  /// <summary>
  /// Adds the texture.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <param name="filePath">The file path.</param>
  /// <param name="useMips">if set to <c>true</c> [use mips].</param>
  void AddTexture(string const& name, string const& filePath, bool useMips = true);

  /// <summary>
  /// Gets the texture.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <returns></returns>
  GLuint GetTexture(string const& name) const;

private:

  /// <summary>
  /// The textures
  /// </summary>
  std::unordered_map<string, GLuint> textures;

};


#endif