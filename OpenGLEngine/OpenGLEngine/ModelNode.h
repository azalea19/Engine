#ifndef ModelNode_h__
#define ModelNode_h__

#include "GL/glew.h"
#include "Node.h"

struct MeshNode;
struct TextureNode;

struct ModelNode : Node
{
	virtual void enter();
	virtual void exit();

private:

	MeshNode* m_mesh;
	TextureNode* m_texture;

};

#endif
