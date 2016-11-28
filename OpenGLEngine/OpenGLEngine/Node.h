#ifndef Node_h__
#define Node_h__

class SceneGraph;

struct Node
{
	Node(SceneGraph* scene);

	virtual void enter() = 0;
	virtual void exit() = 0;

private:

	SceneGraph* m_scene;
};

#endif