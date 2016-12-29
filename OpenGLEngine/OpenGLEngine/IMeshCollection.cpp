#include "IMeshCollection.h"
#include "IMesh.h"
#include "Utility.h"


std::vector<vec3> IMeshCollection::GetVertices() const
{
  std::vector<vec3> vertices;
  int meshCount = GetMeshCount();
  vertices.reserve(GetVertexCount());

  for (int i = 0; i < meshCount; i++)
  {
    VectorConcatenate(vertices, GetMesh(i).GetVertices());
  }
  return vertices;
}

std::vector<vec3> IMeshCollection::GetNormals() const
{
  std::vector<vec3> normals;
  int meshCount = GetMeshCount();
  normals.reserve(GetNormalCount());

  for (int i = 0; i < meshCount; i++)
  {
    VectorConcatenate(normals, GetMesh(i).GetNormals());
  }
  return normals;
}

std::vector<int> IMeshCollection::GetIndices() const
{
  std::vector<int> indices;
  int meshCount = GetMeshCount();
  indices.reserve(GetNormalCount());

  for (int i = 0; i < meshCount; i++)
  {
    VectorConcatenate(indices, GetMesh(i).GetIndices());
  }
  return indices;
}

int IMeshCollection::GetVertexCount() const
{
  int count = 0;
  int meshCount = GetMeshCount();

  for (int i = 0; i < meshCount; i++)
  {
    count += GetMesh(i).GetVertexCount();
  }

  return count;
}

int IMeshCollection::GetNormalCount() const
{
  int count = 0;
  int meshCount = GetMeshCount();

  for (int i = 0; i < meshCount; i++)
  {
    count += GetMesh(i).GetNormalCount();
  }

  return count;
}

int IMeshCollection::GetIndexCount() const
{
  int count = 0;
  int meshCount = GetMeshCount();

  for (int i = 0; i < meshCount; i++)
  {
    count += GetMesh(i).GetIndexCount();
  }

  return count;
}
