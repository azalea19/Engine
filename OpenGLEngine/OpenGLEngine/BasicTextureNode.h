#ifndef BasicTextureNode_h__
#define BasicTextureNode_h__

#include "GL/glew.h"
#include "TextureNode.h"
#include "Types.h"

class SceneGraph;


struct BasicTextureNode : TextureNode
{
	BasicTextureNode(SceneGraph* scene, string textureName);

	virtual void enter();
	virtual void exit();

	virtual GLuint GetTextureID();

	void SetTextureName(string textureName);

private:

	string m_textureName;

};

#endif