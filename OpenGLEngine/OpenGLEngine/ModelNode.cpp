#include "ModelNode.h"
#include "MeshNode.h"
#include "TextureNode.h"

void ModelNode::enter()
{
	m_mesh->enter();
	m_texture->enter();

	return exit(); //tail call 
}

void ModelNode::exit()
{
	GLuint gVBO = m_mesh->GetVertexBufferID();
	GLuint gUVBO = m_mesh->GetUVBufferID();
	GLuint gNBO = m_mesh->GetNormalBufferID();

	//TODO: the thing that makes sense here
	//render
	
}

