
#ifndef UberShader_h__
#define UberShader_h__

#include "Types.h"
#include <unordered_map>
#include <typeinfo>
#include <GL/glew.h>
#include <stack>
#include "UniformStack.h"

struct UberShader
{
	UberShader(string name);
	UberShader(string name, string vertFilePath, string fragFilePath);
	~UberShader();


	void Load(string vertFilePath, string fragFilePath);


	void Bind() const;


	void Setup();

	
	unsigned int GetAttributeID(string name) const;

	
	unsigned int GetUniformID(string name) const;

	
	bool HasAttribute(string name) const;

	
	bool HasUniform(string name) const;


	template<typename T>
	void TransmitUniform(string uniformName, T value) const
	{
		if (HasUniform(uniformName))
			TransmitUniform(GetUniformID(uniformName), value);
		else
			printf("No uniform with name %s", uniformName.c_str());
	}


	template <typename T>
	void TransmitUniform(int uniformID, T value) const
	{
		printf("Transmit uniform not defined for this type %s", typeid(T).name);
	}


	template <>
	void TransmitUniform(int uniformID, float value) const
	{
		glUniform1f(uniformID, value);
	}

	
	template <>
	void TransmitUniform(int uniformID, int value) const
	{
		glUniform1i(uniformID, value);
	}

	
	template <>
	void TransmitUniform(int uniformID, mat4 matrix) const
	{
		glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(matrix));
	}


	template <>
	void TransmitUniform(int uniformID, vec3 vector) const
	{
		glUniform3fv(uniformID, 1, glm::value_ptr(vector));
	}

	template<typename T>
	void AddUniform(string name, T const& defaultValue)
	{
		Gluint uniformID = glGetUniformLocation(m_uid, name.c_str());
		m_uniforms.emplace(name, uniformID);

		UniformStack* st = new UniformStack(defaultValue);
		m_uniformStacks.emplace(uniformID, st);
	}

	template<typename T>
	void AddAttribute(string name)
	{
		Gluint attributeID = glGetAttribLocation(m_uid, name.c_str());
		m_attributes.emplace(name, attributeID);
	}

	template<typename T>
	void PushUniform(string name, T const& value)
	{
		PushUniform(GetUniformID(name), value);
	}

	template<typename T>
	void PushUniform(int uniformID, T const& value)
	{
		UniformStack* st = m_uniformStacks[uniformID];
		switch (st->m_type)
		{
			case ut_int:
				((std::stack<int>*)(st->m_stack))->push(value);
			case ut_vec3:
				((std::stack<vec3>*)(st->m_stack))->push(value);
			case ut_mat4:
				((std::stack<mat4>*)(st->m_stack))->push(value);
		}
		transmitUniform(uniformID, value);
	}

	void PopUniform(string name)
	{
		PopUniform(GetUniformID(name));
	}

	void PopUniform(int uniformID)
	{
		UniformStack* st = m_uniformStacks[uniformID];
		switch (st->m_type)
		{
			case ut_int:
			{
				std::stack<int>* st2 = (std::stack<int>*)(st->m_stack);
				st2->pop();
				TransmitUniform(uniformID, st2->top());
			}
			case ut_vec3:
			{
				std::stack<vec3>* st2 = (std::stack<vec3>*)(st->m_stack);
				st2->pop();
				TransmitUniform(uniformID, st2->top());
			}
			case ut_mat4:
			{
				std::stack<mat4>* st2 = (std::stack<mat4>*)(st->m_stack);
				st2->pop();
				TransmitUniform(uniformID, st2->top());
			}
		}
	}

	void BindAttribute(GLuint bufferID, string name, GLenum type, GLuint size, GLuint stride = 0);

	void UnbindAttribute(string name);

	void BindTexture(GLuint textureID, string samplerName);

private:

	string m_name;
	unsigned int m_uid;
	const char* m_vertex;
	const char* m_fragment;

	std::unordered_map<string, int> m_attributes;
	std::unordered_map<string, int> m_uniforms;
	std::unordered_map<int, UniformStack*> m_uniformStacks;
};

#endif

