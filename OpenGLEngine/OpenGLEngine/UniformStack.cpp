#include "UniformStack.h"
#include <stack>
#include "Types.h"

UniformStack::UniformStack(int const& defaultValue)
	: m_type(ut_int)
{
	m_stack = new std::stack<int>();
}

UniformStack::UniformStack(vec3 const& defaultValue)
	: m_type(ut_vec3)
{
	m_stack = new std::stack<vec3>();
}

UniformStack::UniformStack(mat4 const& defaultValue)
	: m_type(ut_mat4)
{
	m_stack = new std::stack<mat4>();
}

UniformStack::~UniformStack()
{
	switch (m_type)
	{
		case ut_int:
			delete ((std::stack<int>*)m_stack);
			break;
		case ut_vec3:
			delete ((std::stack<vec3>*)m_stack);
			break;
		case ut_mat4:
			delete ((std::stack<mat4>*)m_stack);
			break;
	}
}