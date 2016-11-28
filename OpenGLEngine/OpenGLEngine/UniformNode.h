#ifndef UniformNode_h__
#define UniformNode_h__

#include "GroupNode.h"

template<typename T>
struct UniformNode : GroupNode
{
	UniformNode(SceneGraph* scene);

	virtual void enter();
	virtual void exit();

private:

	string name;
	T value;

};

#endif

template<typename T>
UniformNode<T>::UniformNode(SceneGraph * scene)
	:GroupNode(scene)
{
}

template<typename T>
void UniformNode<T>::enter()
{
	//Push the uniform on to stack
	GroupNode::enter();

	return exit();
}

template<typename T>
void UniformNode<T>::exit()
{
	//Pop uniform off the stack
}
