#include "BasicMeshNode.h"

void BasicMeshNode::enter()
{
}

void BasicMeshNode::exit()
{
}

GLuint BasicMeshNode::GetVertexBufferID()
{
	return m_VertexBufferID;
}

GLuint BasicMeshNode::GetUVBufferID()
{
	return m_UVBUfferID;
}

GLuint BasicMeshNode::GetNormalBufferID()
{
	return m_NormalBufferID;
}

void BasicMeshNode::SetVertexBufferID(GLuint ID)
{
	m_VertexBufferID = ID;
}

void BasicMeshNode::SetUVBufferID(GLuint ID)
{
	m_UVBUfferID = ID;
}

void BasicMeshNode::SetNormalBufferID(GLuint ID)
{
	m_NormalBufferID = ID;
}

BasicMeshNode::BasicMeshNode(SceneGraph * scene)
	: MeshNode(scene)
{

}
