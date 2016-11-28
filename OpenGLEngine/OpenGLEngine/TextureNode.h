#ifndef TextureNode_h__
#define TextureNode_h__

#include "GL/glew.h"
#include "Node.h"

class SceneGraph;

struct TextureNode : Node
{
	TextureNode(SceneGraph* scene);

	virtual void enter() = 0;
	virtual void exit() = 0;
	
	virtual GLuint GetTextureID() = 0;

};

#endif