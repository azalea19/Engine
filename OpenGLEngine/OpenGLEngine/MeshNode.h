#ifndef MeshNode_h__
#define MeshNode_h__

#include "Node.h"
#include "GL/glew.h"

struct MeshNode : public Node
{

	MeshNode(SceneGraph* scene);

	virtual void enter() = 0;
	virtual void exit() = 0;

	virtual GLuint GetVertexBufferID() = 0;
	virtual GLuint GetUVBufferID() = 0;
	virtual GLuint GetNormalBufferID() = 0;
	virtual GLuint GetVertexCount() = 0;

};

#endif