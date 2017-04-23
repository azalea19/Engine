#ifndef IMesh_h__
#define IMesh_h__

#include "Types.h"

/**
* @file IMesh.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief An interface that allows the user to add functionality associated with a mesh object.
*
*/

class IMesh
{
public:

  /// <summary>
  /// Gets the vertices.
  /// </summary>
  /// <returns>std::vector<vec3></returns>
  virtual std::vector<vec3> const& GetVertices() const = 0;

  /// <summary>
  /// Gets the normals.
  /// </summary>
  /// <returns>std::vector<vec3></returns>
  virtual std::vector<vec3> const& GetNormals() const = 0;

  /// <summary>
  /// Gets the indices.
  /// </summary>
  /// <returns>std::vector<vec3></returns>
  virtual std::vector<int> const& GetIndices() const = 0;


  virtual std::vector<vec2> const& GetTexCoords() const;

  
  int GetTexCoordsCount() const;


  /// <summary>
  /// Gets the vertex count.
  /// </summary>
  /// <returns></returns>
  int GetVertexCount() const;

  /// <summary>
  /// Gets the normal count.
  /// </summary>
  /// <returns></returns>
  int GetNormalCount() const;

  /// <summary>
  /// Gets the index count.
  /// </summary>
  /// <returns></returns>
  int GetIndexCount() const;

};


#endif // IMesh_h__
