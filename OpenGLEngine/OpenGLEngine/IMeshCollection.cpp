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

std::vector<vec3> IMeshCollection::GetAABB() const
{

	std::vector<vec3> aabb;

	int meshCount = GetMeshCount();

	for (int i = 0; i < meshCount; i++)
	{
		std::vector<vec3> verts = GetMesh(i).GetVertices();

		for (int a = 0; a < verts.size(); a++)
		{
			// Set up min and max to the first values to initialise
			if (i == 0 && a == 0)
			{
				aabb.push_back(verts[a]);
				aabb.push_back(verts[a]);
			}

			// Check for new min and max values
			if (verts[a].x < aabb[0].x)
			{
				aabb[0].x = verts[a].x;
			}
			if (verts[a].y < aabb[0].y)
			{
				aabb[0].y = verts[a].y;
			}
			if (verts[a].z < aabb[0].z)
			{
				aabb[0].z = verts[a].z;
			}

			if (verts[a].x > aabb[1].x)
			{
				aabb[1].x = verts[a].x;
			}
			if (verts[a].y > aabb[1].y)
			{
				aabb[1].y = verts[a].y;
			}
			if (verts[a].z > aabb[1].z)
			{
				aabb[1].z = verts[a].z;
			}
		}
		
	}


	return aabb;
}
