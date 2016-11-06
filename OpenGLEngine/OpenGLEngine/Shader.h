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

	/**
	* @brief Loads the vertex shader and fragment shader from their respective files
	* and sets up the various uniforms and attributes it needs access to
	*
	* @param vertFilePath - the file path of the vertex shader
	* @param fragFilePath - the file path of the fragment shader
	* @param attributes - the vector string attributes the shader requires
	* @param uniforms - the vector of uniforms that the shader requires
	*
	* @return void
	*/
	void load(string vertFilePath,string fragFilePath, std::vector<string> attributes, std::vector<string> uniforms);

	/**
	* @brief Binds the shader by setting it as the active shader program
	*
	* @return void
	*/
	void bind() const;

	/**
	* @brief The setup method creates a new program, attaches the compiled vertex and fragment shaders
	* and links them to create a usable shader program
	*
	* @return void
	*/
	void setup();

	/**
	* @brief Sets up the attribute and uniform locations required by the shader
	*
	* @param custom_attributes - the vector of attributes required for the shader
	* @param custom_uniforms - the vector of uniforms required for the shader
	*
	* @return void
	*/
	void setupLocations(std::vector<string> custom_attributes, std::vector<string> custom_uniforms);

	/**
	* @brief Returns the name of the shader
	*
	* @return string
	*/
	string getName() const;

	/**
	* @brief Returns the attribute with the specified name
	*
	* @param name - the name of the attribute
	*
	* @return unsigned int
	*/
	unsigned int attribute(string name) const;

	/**
	* @brief Returns the uniform with the specified name
	*
	* @param name - the name of the uniform
	*
	* @return unsigned int
	*/
	unsigned int uniform(string name) const;

	/**
	* @brief Returns whether the shader has the specified attribute
	*
	* @param name - the name of the attribute
	*
	* @return bool
	*/
	bool hasAttribute(string name) const;

	/**
	* @brief Returns whether the shader has the specified uniform
	*
	* @param name - the name of the uniform
	*
	* @return bool
	*/
	bool hasUniform(string name) const;


	/**
	* @brief The transmit uniform function transmits the specified uniform 
	* to the shader if the shader has the specified uniform name in it's map and there is a function
	* transmitUniform that exists to deal with the value type
	*
	* @param uniformName - the name of the uniform
	* @param value - the value of that uniform
	*
	* @return void
	*/
	template<typename T>
	void transmitUniform(string uniformName, T value) const
	{
		if (hasUniform(uniformName))
			transmitUniform(uniform(uniformName), value);
		else
			printf("No uniform with name %s", uniformName.c_str());
	}


	/**
	* @brief This transmit uniform function is called when the transmit uniform function
	* is undefined for the uniform type to be transmitted
	*
	* @param uniformName - the name of the uniform
	* @param value - the value of that uniform
	*
	* @return void
	*/
	template <typename T>
	void transmitUniform(int uniformID, T value) const
	{
		printf("Transmit uniform not defined for this type %s", typeid(T).name);
	}

	/**
	* @brief This transmit uniform function is called when the value to transmit is a float
	*
	* @param uniformName - the name of the uniform
	* @param value - the value of that uniform
	*
	* @return void
	*/
	template <>
	void transmitUniform(int uniformID, float value) const
	{
		glUniform1f(uniformID, value);
	}

	/**
	* @brief This transmit uniform function is called when the value to transmit is an int
	*
	* @param uniformName - the name of the uniform
	* @param value - the value of that uniform
	*
	* @return void
	*/
	template <>
	void transmitUniform(int uniformID, int value) const
	{
		glUniform1i(uniformID, value);
	}

	/**
	* @brief This transmit uniform function is called when the value to transmit is a mat4
	*
	* @param uniformName - the name of the uniform
	* @param value - the value of that uniform
	*
	* @return void
	*/
	template <>
	void transmitUniform(int uniformID, mat4 matrix) const
	{
		glUniformMatrix4fv(uniformID,1, GL_FALSE, glm::value_ptr(matrix));
	}

	/**
	* @brief This transmit uniform function is called when the value to transmit is a vec3
	*
	* @param uniformName - the name of the uniform
	* @param value - the value of that uniform
	*
	* @return void
	*/
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

