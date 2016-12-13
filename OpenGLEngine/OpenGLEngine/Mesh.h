#ifndef Mesh_h__
#define Mesh_h__

#include "Types.h"
#include "GL/glew.h"

struct Mesh
{
	GLuint m_vertexBufferID;
	GLuint m_normalBufferID;
	GLuint m_uvBufferID;
	GLuint m_vertexCount;
};

struct MeshData
{
	std::vector<vec3> m_vertexBuffer;
	std::vector<vec3> m_normalBuffer;
	std::vector<vec2> m_uvBuffer;
};

#endif