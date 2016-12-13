#include "MeshLibrary.h"

void MeshLibrary::AddMesh(string name, MeshData const& mesh)
{
	Mesh m;

	glGenBuffers(1, &m.m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m.m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, mesh.m_vertexBuffer.size() * sizeof(GLfloat), mesh.m_vertexBuffer.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m.m_uvBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m.m_uvBufferID);
	glBufferData(GL_ARRAY_BUFFER, mesh.m_uvBuffer.size() * sizeof(GLfloat), mesh.m_uvBuffer.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m.m_normalBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m.m_normalBufferID);
	glBufferData(GL_ARRAY_BUFFER, mesh.m_normalBuffer.size() * sizeof(GLfloat), mesh.m_normalBuffer.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	m.m_vertexCount = mesh.m_vertexBuffer.size();

	meshes.emplace(name, m);
}

Mesh MeshLibrary::GetMesh(string name)
{
	std::unordered_map<string, Mesh>::const_iterator got = meshes.find(name);
	if (got == meshes.end())
	{
		printf("Mesh with name %s not found.", name.c_str());
		return Mesh{ GLuint(-1),GLuint(-1),GLuint(-1) };
	}
	else
		return got->second;
}
