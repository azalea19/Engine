#ifndef UniformStack_h__
#define UniformStack_h__

#include "Types.h"

enum UniformType
{
	ut_int,
	ut_vec3,
	ut_mat4
};

struct UniformStack
{
	UniformStack(int const & defaultValue);
	UniformStack(vec3 const & defaultValue);
	UniformStack(mat4 const & defaultValue);
	~UniformStack();

	void* m_stack;
	UniformType m_type;
};

#endif