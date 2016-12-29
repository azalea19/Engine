#ifndef IMeshCollection_h__
#define IMeshCollection_h__

#include "Types.h"

class IMesh;

class IMeshCollection 
{
public:

  std::vector<vec3> GetVertices() const;
  std::vector<vec3> GetNormals() const;
  std::vector<int> GetIndices() const;

  int GetVertexCount() const;
  int GetNormalCount() const;
  int GetIndexCount() const;

  virtual IMesh const& GetMesh(int meshIndex) const = 0;
  virtual int GetMeshCount() const = 0;

private:

};


#endif // IMeshCollection_h__
