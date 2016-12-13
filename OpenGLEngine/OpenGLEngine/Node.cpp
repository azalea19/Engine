#include "Node.h"

Node::Node(SceneGraph * scene)
{
	m_sceneGraph = scene;
}

SceneGraph * Node::GetSceneGraph()
{
	return m_sceneGraph;
}
