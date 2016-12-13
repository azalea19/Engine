#ifndef BasicMeshNode_h__
#define BasicMeshNode_h__

#include "MeshNode.h"
#include "GL/glew.h"
#include "Types.h"

struct BasicMeshNode : public MeshNode
{
	BasicMeshNode(SceneGraph* scene, string meshName);

	virtual void enter();
	virtual void exit();

	virtual GLuint GetVertexBufferID();
	virtual GLuint GetUVBufferID();
	virtual GLuint GetNormalBufferID();
	virtual GLuint GetVertexCount();

	void SetMesh(string name);

private:
	string m_meshName;
};

#endif