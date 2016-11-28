#ifndef MatrixNode_h__
#define MatrixNode_h__

#include "Types.h"

struct MatrixNode
{
	virtual void enter() = 0;
	virtual void exit() = 0;

	mat4 GetMatrix();
	void SetMatrix(mat4 matrix);

private:

	mat4 m_matrix;
};

#endif