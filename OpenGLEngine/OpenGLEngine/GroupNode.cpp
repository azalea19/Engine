#include "GroupNode.h"

GroupNode::GroupNode(SceneGraph * scene)
	: Node(scene)
{

}

void GroupNode::enter()
{
	for (int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->enter();
	}

	return exit();
}

void GroupNode::exit()
{
}
