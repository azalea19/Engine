#ifndef ModelNode_h__
#define ModelNode_h__

#include "GL/glew.h"
#include "Node.h"

struct MeshNode;
struct TextureNode;

struct ModelNode : public Node
{
	ModelNode(SceneGraph* sceneGraph);
	virtual void enter();
	virtual void exit();

	void SetMeshNode(MeshNode* node);
	void SetTextureNode(TextureNode* node);

private:

	MeshNode* m_mesh;
	TextureNode* m_texture;
};

#endif
