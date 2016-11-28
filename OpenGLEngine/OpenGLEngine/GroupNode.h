#ifndef GroupNode_h__
#define GroupNode_h__

#include "Node.h"
#include "Types.h"

class SceneGraph;

struct GroupNode : Node
{
	GroupNode(SceneGraph* scene);

	virtual void enter();
	virtual void exit();

private:

	std::vector<Node*> m_children;
};

#endif