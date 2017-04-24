#ifndef Shader_h__
#define Shader_h__

#include "Types.h"
#include <unordered_map>
#include <typeinfo>
#include <GL/glew.h>
#include "IShader.h"

/**
* @file   Shader.h
* @Author Maddisen Topaz
* @date   S1, 2017
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

class Shader : public IShader
{
public:

  /// <summary>
  /// Initializes a new instance of the <see cref="Shader"/> class.
  /// </summary>
  /// <param name="name">The name.</param>
  Shader(string const& name);
	
  /// <summary>
  /// Initializes a new instance of the <see cref="Shader"/> class.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <param name="vertFilePath">The vert file path.</param>
  /// <param name="fragFilePath">The frag file path.</param>
  /// <param name="attributes">The attributes.</param>
  /// <param name="uniforms">The uniforms.</param>
  Shader(string const& name, string const& vertFilePath, string const& fragFilePath, std::vector<string> const& attributes, std::vector<string> const& uniforms);
	
  /// <summary>
  /// Finalizes an instance of the <see cref="Shader"/> class.
  /// </summary>
  ~Shader();


  /// <summary>
  /// Loads the specified shader files.
  /// </summary>
  /// <param name="vertFilePath">The vert file path.</param>
  /// <param name="fragFilePath">The frag file path.</param>
  /// <param name="attributes">The attributes.</param>
  /// <param name="uniforms">The uniforms.</param>
  void Load(string const& vertFilePath, string const& fragFilePath, std::vector<string> const& attributes, std::vector<string> const& uniforms);


  /// <summary>
  /// Binds this instance.
  /// </summary>
  virtual void Bind() const override;


  /// <summary>
  /// Setups this instance.
  /// </summary>
  void Setup();


  /// <summary>
  /// Setups the locations.
  /// </summary>
  /// <param name="custom_attributes">The custom attributes.</param>
  /// <param name="custom_uniforms">The custom uniforms.</param>
  void SetupLocations(std::vector<string> const& custom_attributes, std::vector<string> const& custom_uniforms);


  /// <summary>
  /// Gets the name.
  /// </summary>
  /// <returns></returns>
  virtual string const& GetName() const override;


  /// <summary>
  /// Returns the attribute with the specified name.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <returns>int</returns>
  virtual unsigned int Attribute(string const& name) const override;


  /// <summary>
  /// Returns the uniform with the specified name.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <returns>int</returns>
  virtual unsigned int Uniform(string const& name) const override;

  /// <summary>
  /// Determines whether the specified shader has attribute.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <returns>
  ///   <c>true</c> if the specified name has attribute; otherwise, <c>false</c>.
  /// </returns>
  virtual bool HasAttribute(string const& name) const override;


  /// <summary>
  /// Determines whether the specified shader has uniform.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <returns>
  ///   <c>true</c> if the specified name has uniform; otherwise, <c>false</c>.
  /// </returns>
  virtual bool HasUniform(string const& name) const override;


	virtual void TransmitUniform(string const& uniformID, float const& value) const override
	{
    int uniformIDint = Uniform(uniformID);
		glUniform1f(uniformIDint, value);
	}

	virtual void TransmitUniform(string const& uniformID, int const& value) const override
	{
    int uniformIDint = Uniform(uniformID);
		glUniform1i(uniformIDint, value);
	}


	virtual void TransmitUniform(string const& uniformID, mat4 const& matrix) const override
	{
    int uniformIDint = Uniform(uniformID);
		glUniformMatrix4fv(uniformIDint,1, GL_FALSE, glm::value_ptr(matrix));
	}


	virtual void TransmitUniform(string const& uniformID, vec3 const& vector) const override
	{
    int uniformIDint = Uniform(uniformID);
		glUniform3fv(uniformIDint, 1, glm::value_ptr(vector));
	}

  virtual void TransmitUniform(string const& uniformID, vec2 const& vector) const override
  {
    int uniformIDint = Uniform(uniformID);
    glUniform2fv(uniformIDint, 1, glm::value_ptr(vector));
  }

	virtual void TransmitUniformArray(string const& uniformID, mat4* matrix, int count) const override
	{

    int uniformIDint = Uniform(uniformID);
		glUniformMatrix4fv(uniformIDint, count, GL_FALSE, (GLfloat*)matrix);
	}


private:

  /// <summary>
  /// The m name
  /// </summary>
  string m_name;

  /// <summary>
  /// The shaders ID
  /// </summary>
  unsigned int m_uid;

  /// <summary>
  /// The vertex shader
  /// </summary>
  const char* m_pVertex;

  /// <summary>
  /// The fragment shader
  /// </summary>
  const char* m_pFragment;

  /// <summary>
  /// The attributes
  /// </summary>
  std::unordered_map<string, int> m_attributes;

  /// <summary>
  /// The uniforms
  /// </summary>
  std::unordered_map<string, int> m_uniforms;

};

#endif

