#ifndef IMeshCollection_h__
#define IMeshCollection_h__

#include "Types.h"

/**
* @file IMeshCollection.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief An interface that allows the user to add functionality associated with a collection of meshes.
*
*/

class IMesh;

class IMeshCollection 
{
public:

  /// <summary>
  /// Gets the vertices.
  /// </summary>
  /// <returns></returns>
  std::vector<vec3> GetVertices() const;

  /// <summary>
  /// Gets the normals.
  /// </summary>
  /// <returns></returns>
  std::vector<vec3> GetNormals() const;

  /// <summary>
  /// Gets Axis aligned bounding box - index 0=min, 1=max.
  /// </summary>
  /// <returns></returns>
  std::vector<vec3> GetAABB() const;

  /// <summary>
  /// Gets the indices.
  /// </summary>
  /// <returns></returns>
  std::vector<int> GetIndices() const;

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

  /// <summary>
  /// Gets the mesh at the specified index.
  /// </summary>
  /// <param name="meshIndex">Index of the mesh.</param>
  /// <returns></returns>
  virtual IMesh const& GetMesh(int meshIndex) const = 0;

  /// <summary>
  /// Gets the mesh count.
  /// </summary>
  /// <returns></returns>
  virtual int GetMeshCount() const = 0;


};


#endif // IMeshCollection_h__
