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

enum Attribute_Location
{
  AL_Vertices = 0,
  AL_DiffuseTexCoords = 1,
  AL_AlphaTexCoords = 2,
  AL_Normals = 3,
  AL_BoneIDs = 4,
  AL_BoneWeights = 5,
  AL_VertexColours = 6,
};

class Shader
{
public:

	Shader(string const& name);
	Shader(string const& name, string const& vertFilePath, string const& fragFilePath, std::vector<string> const& attributes, std::vector<string> const& uniforms);
	~Shader();


	void Load(string const& vertFilePath,string const& fragFilePath, std::vector<string> const& attributes, std::vector<string> const& uniforms);


	void Bind() const;


	void Setup();


	void SetupLocations(std::vector<string> const& custom_attributes, std::vector<string> const& custom_uniforms);


	string GetName() const;


	unsigned int Attribute(string const& name) const;


	unsigned int Uniform(string const& name) const;

	bool HasAttribute(string const& name) const;


	bool HasUniform(string const& name) const;


	template<typename T>
	void TransmitUniform(string const& uniformName, T value) const
	{
		if (HasUniform(uniformName))
			TransmitUniform(Uniform(uniformName), value);
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
	void TransmitUniform(int uniformID, mat4 const& matrix) const
	{
		glUniformMatrix4fv(uniformID,1, GL_FALSE, glm::value_ptr(matrix));
	}


	template <>
	void TransmitUniform(int uniformID, vec3 const& vector) const
	{
		glUniform3fv(uniformID, 1, glm::value_ptr(vector));
	}

  template <>
  void TransmitUniform(int uniformID, vec2 const& vector) const
  {
    glUniform2fv(uniformID, 1, glm::value_ptr(vector));
  }

	template<typename T>
	void TransmitUniformArray(string const& uniformName, T* value, int count) const
	{
		if (HasUniform(uniformName))
			TransmitUniformArray(Uniform(uniformName), value, count);
		else
			printf("No uniform with name %s", uniformName.c_str());
	}

	template <typename T>
	void TransmitUniformArray(int uniformID, T* value, int count) const
	{
		printf("Transmit uniform not defined for this type %s", typeid(T).name);
	}

	template <>
	void TransmitUniformArray(int uniformID, mat4* matrix, int count) const
	{
		glUniformMatrix4fv(uniformID, count, GL_FALSE, (GLfloat*)matrix);
	}


private:

	string m_name;
	unsigned int m_uid;
	const char* m_pVertex;
	const char* m_pFragment;

	std::unordered_map<string, int> m_attributes;
	std::unordered_map<string, int> m_uniforms;

};

#endif

