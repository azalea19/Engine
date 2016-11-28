#include "BasicTextureNode.h"

BasicTextureNode::BasicTextureNode(SceneGraph * scene)
	: TextureNode(scene)
{

}

void BasicTextureNode::enter()
{
}

void BasicTextureNode::exit()
{
}

GLuint BasicTextureNode::GetTextureID()
{
	return m_textureID;
}

void BasicTextureNode::SetTextureID(GLuint ID)
{
	m_textureID = ID;
}
