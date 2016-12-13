#include "BasicTextureNode.h"
#include "TextureLibrary.h"

BasicTextureNode::BasicTextureNode(SceneGraph * scene, string textureName)
	: TextureNode(scene)
	, m_textureName(textureName)
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
	return TextureLibrary::GetInstance().GetTexture(m_textureName);
}

void BasicTextureNode::SetTextureName(string textureName)
{
	m_textureName = textureName;
}
