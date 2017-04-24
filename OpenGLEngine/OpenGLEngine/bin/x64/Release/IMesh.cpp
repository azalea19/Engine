#include "IMesh.h"

std::vector<vec2> const& IMesh::GetTexCoords() const
{
  throw new std::logic_error("Not implemented.");
}

int IMesh::GetTexCoordsCount() const
{
  return GetTexCoords().size();
}

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


