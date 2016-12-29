#include "IMesh.h"

int IMesh::GetVertexCount() const
{
  return GetVertices().size();
}

int IMesh::GetNormalCount() const
{
  return GetNormals().size();
}

int IMesh::GetIndexCount() const
{
  return GetIndices().size();
}
