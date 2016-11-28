#ifndef BasicMeshNode_h__
#define BasicMeshNode_h__

#include "MeshNode.h"
#include "GL/glew.h"

struct BasicMeshNode : public MeshNode
{
	BasicMeshNode(SceneGraph* scene);

	virtual void enter();
	virtual void exit();

	virtual GLuint GetVertexBufferID();
	virtual GLuint GetUVBufferID();
	virtual GLuint GetNormalBufferID();

	void SetVertexBufferID(GLuint ID);
	void SetUVBufferID(GLuint ID);
	void SetNormalBufferID(GLuint ID);

private:

	GLuint m_VertexBufferID;
	GLuint m_NormalBufferID;
	GLuint m_UVBUfferID;

};

#endif