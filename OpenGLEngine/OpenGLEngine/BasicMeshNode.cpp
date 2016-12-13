#include "BasicMeshNode.h"
#include "MeshLibrary.h"

void BasicMeshNode::enter()
{
}

void BasicMeshNode::exit()
{
}

GLuint BasicMeshNode::GetVertexBufferID()
{
	return MeshLibrary::GetInstance().GetMesh(m_meshName).m_vertexBufferID;
}

GLuint BasicMeshNode::GetUVBufferID()
{
	return MeshLibrary::GetInstance().GetMesh(m_meshName).m_uvBufferID;
}

GLuint BasicMeshNode::GetNormalBufferID()
{
	return MeshLibrary::GetInstance().GetMesh(m_meshName).m_normalBufferID;
}

GLuint BasicMeshNode::GetVertexCount()
{
	return MeshLibrary::GetInstance().GetMesh(m_meshName).m_vertexCount;
}

void BasicMeshNode::SetMesh(string name)
{
	m_meshName = name;
}

BasicMeshNode::BasicMeshNode(SceneGraph * scene, string meshName)
	: MeshNode(scene)
	, m_meshName(meshName)
{

}
