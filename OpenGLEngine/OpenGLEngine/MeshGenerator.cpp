#include "MeshGenerator.h"
#include "Mesh.h"
#include <cstdlib>

void CreateHeightMapVertices(int64_t width, int64_t height, float* heightMap, MeshData* mesh)
{
	for (int64_t z = 0; z < height - 1; z++)
	{
		for (int64_t x = 0; x < width - 1; x++)
		{
			glm::vec3 corners[4];
			corners[0] = vec3(x, heightMap[z * width + x], z);
			corners[1] = vec3(x, heightMap[(z + 1) * width + x], (z + 1));
			corners[2] = vec3(x + 1, heightMap[(z + 1) * width + x + 1], (z + 1));
			corners[3] = vec3(x + 1, heightMap[z * width + x + 1], z);

			mesh->m_vertexBuffer.push_back(corners[0]);
			mesh->m_vertexBuffer.push_back(corners[1]);
			mesh->m_vertexBuffer.push_back(corners[3]);

			mesh->m_vertexBuffer.push_back(corners[1]);
			mesh->m_vertexBuffer.push_back(corners[2]);
			mesh->m_vertexBuffer.push_back(corners[3]);
		}
	}
			
}

void CreateFlatNormals(MeshData* mesh)
{
	for (int64_t i = 0; i < mesh->m_vertexBuffer.size(); i += 3)
	{
		vec3 a = mesh->m_vertexBuffer[i];
		vec3 b = mesh->m_vertexBuffer[i + 1];
		vec3 c = mesh->m_vertexBuffer[i + 2];

		vec3 ab = glm::normalize(b - a);
		vec3 ac = glm::normalize(c - a);

		vec3 normal = glm::normalize(glm::cross(ac, ab));

		mesh->m_normalBuffer.push_back(normal);
		mesh->m_normalBuffer.push_back(normal);
		mesh->m_normalBuffer.push_back(normal);
	}
}

void CreateUVs(MeshData* mesh)
{
	for (int64_t i = 0; i < mesh->m_vertexBuffer.size(); i++)
	{
		mesh->m_uvBuffer.push_back(vec2(0, 0));
	}
}

MeshData * CreateMeshFromHeightMap(int64_t width, int64_t height, float * heightMap)
{
	MeshData *mesh = new MeshData();

	CreateHeightMapVertices(width, height, heightMap, mesh);
	CreateFlatNormals(mesh);
	CreateUVs(mesh);

	return mesh;
}
