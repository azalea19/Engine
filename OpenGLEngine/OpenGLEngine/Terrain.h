#ifndef Terrain_h__
#define Terrain_h__

#include "Types.h"
#include "HeightMap.h"
#include <GL/glew.h>
#include "IMesh.h"
#include "OBJWriter.h"
#include <string>


/**
* @file Terrain.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief A class used to generate a terrain mesh.
*
*/

class Terrain : public IMesh
{
public:

  /// <summary>
  /// Initializes a new instance of the <see cref="Terrain"/> class.
  /// </summary>
  /// <param name="terrainWidth">Width of the terrain.</param>
  /// <param name="terrainHeight">Height of the terrain.</param>
  /// <param name="heightScale">The height scale.</param>
  /// <param name="filepath">The filepath.</param>
  Terrain(uint terrainWidth, uint terrainHeight, float heightScale, string const& filepath);

  /// <summary>
  /// Creates the mesh.
  /// </summary>
  void CreateMesh();

  /// <summary>
  /// Gets the height map.
  /// </summary>
  /// <returns>Heightmap</returns>
  HeightMap* GetHeightMap();

  /// <summary>
  /// Gets the x block scale.
  /// </summary>
  /// <returns>float</returns>
  float GetXBlockScale() const;

  /// <summary>
  /// Gets the y block scale.
  /// </summary>
  /// <returns>float</returns>
  float GetYBlockScale() const;

  /// <summary>
  /// Gets the height scale.
  /// </summary>
  /// <returns>float</returns>
  float GetHeightScale() const;

  /// <summary>
  /// Gets the vertices.
  /// </summary>
  /// <returns>std::vector<vec3></returns>
  virtual std::vector<vec3> const& GetVertices() const override;

  /// <summary>
  /// Gets the normals.
  /// </summary>
  /// <returns>std::vector<vec3></returns>
  virtual std::vector<vec3> const& GetNormals() const override;

  /// <summary>
  /// Gets the indices.
  /// </summary>
  /// <returns>std::vector<int></returns>
  virtual std::vector<int> const& GetIndices() const override;

  virtual std::vector<vec2> const& GetTexCoords() const override;

private:

  /// <summary>
  /// The vertex buffer object
  /// </summary>
  GLuint gVBO;

  /// <summary>
  /// The normals buffer object
  /// </summary>
  GLuint gNBO;

  /// <summary>
  /// The index buffer object
  /// </summary>
  GLuint gIBO;

  /// <summary>
  /// The uvs buffer object
  /// </summary>
  GLuint gUVBO;

  GLuint m_texture;

  /// <summary>
  /// The vertices
  /// </summary>
  std::vector<vec3> m_vertices;

  /// <summary>
  /// The normals
  /// </summary>
  std::vector<vec3> m_normals;

  /// <summary>
  /// The indices
  /// </summary>
  std::vector<int> m_indices;

  /// <summary>
  /// The texture coords
  /// </summary>
  std::vector<vec2> m_texCoords;

  /// <summary>
  /// The height map
  /// </summary>
  HeightMap* m_pHeightMap;

  /// <summary>
  /// The height scale
  /// </summary>
  float m_heightScale;

  /// <summary>
  /// The x block scale
  /// </summary>
  float m_xBlockScale;

  /// <summary>
  /// The y block scale
  /// </summary>
  float m_yBlockScale;

  /// <summary>
  /// The terrain width
  /// </summary>
  float m_terrainWidth;

  /// <summary>
  /// The terrain height
  /// </summary>
  float m_terrainHeight;

  /// <summary>
  /// The texture width
  /// </summary>
  float m_textureWidth;

  /// <summary>
  /// The texture height
  /// </summary>
  float m_textureHeight;

  /// <summary>
  /// Generates the texture coords.
  /// </summary>
  void GenerateTexCoords();
  
  /// <summary>
  /// Generates the terrain indices.
  /// </summary>
  void GenerateTerrainIndices();
  
  /// <summary>
  /// Generates the terrain vertices.
  /// </summary>
  void GenerateTerrainVertices();
  
  /// <summary>
  /// Generates the normals.
  /// </summary>
  void GenerateNormals();

};


#endif // Terrain_h__
