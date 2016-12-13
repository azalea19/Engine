#include "ModelNode.h"
#include "MeshNode.h"
#include "TextureNode.h"
#include "SceneGraph.h"
#include "UberShader.h"

ModelNode::ModelNode(SceneGraph * sceneGraph)
	: Node(sceneGraph)
	, m_mesh(nullptr)
	, m_texture(nullptr)
{
}

void ModelNode::enter()
{
	m_mesh->enter();
	//m_texture->enter();

	return exit(); //tail call 
}

void ModelNode::exit()
{
	GLuint vertexCount = m_mesh->GetVertexCount();
	GLuint gVBO = m_mesh->GetVertexBufferID();
	GLuint gUVBO = m_mesh->GetUVBufferID();
	GLuint gNBO = m_mesh->GetNormalBufferID();
	//GLuint texID = m_texture->GetTextureID();

	UberShader* shader = GetSceneGraph()->GetShader();

	shader->BindAttribute(gVBO, "position", GL_FLOAT, 3);
	shader->BindAttribute(gUVBO, "uv", GL_FLOAT, 2);
	shader->BindAttribute(gNBO, "normal", GL_FLOAT, 3);
	//shader->BindTexture(texID, "diffuse");

	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	shader->UnbindAttribute("position");
	shader->UnbindAttribute("uv");
	shader->UnbindAttribute("normal");
}

void ModelNode::SetMeshNode(MeshNode * node)
{
	m_mesh = node;
}

void ModelNode::SetTextureNode(TextureNode * node)
{
	m_texture = node;
}

