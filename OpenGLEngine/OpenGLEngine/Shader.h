#ifndef Shader_h__
#define Shader_h__

#include "Types.h"
#include <unordered_map>
#include <typeinfo>
#include <GL/glew.h>

/**
* @file   Shader.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The shader struct.
*
* The shader struct contains all of the data relating to a particular shader program to be stored in the shader library
* 
* I used Lazy Foo's tutorial as a reference for how to setup, compile, link, bind and debug shader programs to create
* a usable shader program 
* See the following:
* http://lazyfoo.net/tutorials/OpenGL/29_hello_glsl/index.php
*/


struct Shader
{
	Shader(string name);
	Shader(string name, string vertFilePath, string fragFilePath, std::vector<string> attributes, std::vector<string> uniforms);
	~Shader();


	void load(string vertFilePath,string fragFilePath, std::vector<string> attributes, std::vector<string> uniforms);


	void bind() const;


	void setup();


	void setupLocations(std::vector<string> custom_attributes, std::vector<string> custom_uniforms);


	string getName() const;


	unsigned int attribute(string name) const;


	unsigned int uniform(string name) const;

	bool hasAttribute(string name) const;


	bool hasUniform(string name) const;


	template<typename T>
	void transmitUniform(string uniformName, T value) const
	{
		if (hasUniform(uniformName))
			transmitUniform(uniform(uniformName), value);
		else
			printf("No uniform with name %s", uniformName.c_str());
	}


	template <typename T>
	void transmitUniform(int uniformID, T value) const
	{
		printf("Transmit uniform not defined for this type %s", typeid(T).name);
	}


	template <>
	void transmitUniform(int uniformID, float value) const
	{
		glUniform1f(uniformID, value);
	}

	template <>
	void transmitUniform(int uniformID, int value) const
	{
		glUniform1i(uniformID, value);
	}


	template <>
	void transmitUniform(int uniformID, mat4 matrix) const
	{
		glUniformMatrix4fv(uniformID,1, GL_FALSE, glm::value_ptr(matrix));
	}


	template <>
	void transmitUniform(int uniformID, vec3 vector) const
	{
		glUniform3fv(uniformID, 1, glm::value_ptr(vector));
	}


private:

	string m_name;
	unsigned int m_uid;
	const char* m_vertex;
	const char* m_fragment;

	std::unordered_map<string, int> m_attributes;
	std::unordered_map<string, int> m_uniforms;

};

#endif

