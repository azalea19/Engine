#ifndef IMesh_h__
#define IMesh_h__

#include "Types.h"

class IMesh
{
public:

  virtual std::vector<vec3> const& GetVertices() const = 0;
  virtual std::vector<vec3> const& GetNormals() const = 0;
  virtual std::vector<int> const& GetIndices() const = 0;
  int GetVertexCount() const;
  int GetNormalCount() const;
  int GetIndexCount() const;

private:
};


#endif // IMesh_h__
