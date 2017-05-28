#ifndef OBJWriter_h__
#define OBJWriter_h__

#include <vector>
#include "IMesh.h"
#include "Types.h"


/**
* @file OBJWriter.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief Used to write a Mesh object out to a file as an OBJ.
*
*/

class OBJWriter
{
public:

  /// <summary>
  /// Saves the mesh to object out to an OBJ file.
  /// </summary>
  /// <param name="model">The model.</param>
  /// <param name="filepath">The filepath.</param>
  static void SaveMeshToOBJ(IMesh const& model, string const& filepath);
};

#endif // OBJWriter_h__
