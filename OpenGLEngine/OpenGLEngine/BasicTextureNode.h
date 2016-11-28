#ifndef BasicTextureNode_h__
#define BasicTextureNode_h__

#include "GL/glew.h"
#include "TextureNode.h"

class SceneGraph;


struct BasicTextureNode : TextureNode
{
	BasicTextureNode(SceneGraph* scene);

	virtual void enter();
	virtual void exit();

	virtual GLuint GetTextureID();

	void SetTextureID(GLuint ID);

private:

	GLuint m_textureID;

};

#endif