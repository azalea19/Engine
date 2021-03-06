#ifndef ShaderLibrary_h__
#define ShaderLibrary_h__

#include "Types.h"
#include "Shader.h"
#include <unordered_map>
#include "Singleton.h"
#include <memory>

class IEngine;

/**
* @file   ShaderLibrary.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief  The shader library.
*
* The shader library contains all of the various shaders we have access to in the program.
*/

struct ShaderLibrary : public Singleton<ShaderLibrary>
{

  /// <summary>
  /// The shaders
  /// </summary>
  std::unordered_map<string, std::unique_ptr<IShader>> shaders;


  /// <summary>
  /// Initializes the shader library.
  /// </summary>
  static void InitShaderLibrary(IEngine const *pEngine);


  /// <summary>
  /// Adds the shader.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <param name="uniforms">The uniforms.</param>
  /// <param name="attributes">The attributes.</param>
  void AddShader(string const& name, std::vector<string> const& uniforms, std::vector<string> const& attributes);

	
  /// <summary>
  /// Gets the shader.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <returns>Shader</returns>
  std::unique_ptr<IShader> const& GetShader(string const& name) const;


  /// <summary>
  /// Binds the shader.
  /// </summary>
  /// <param name="shaderName">Name of the shader.</param>
  void BindShader(string const& shaderName);


  /// <summary>
  /// Binds the default shader.
  /// </summary>
  void BindDefaultShader();


  /// <summary>
  /// Return the current shader bound.
  /// </summary>
  /// <returns>Shader</returns>
  std::unique_ptr<IShader> const& ShaderLibrary::CurrentShader() const;

	
  /// <summary>
  /// Gets the name of the current shader.
  /// </summary>
  /// <returns>string</returns>
  string const& GetCurrentShaderName() const;

private:

  /// <summary>
  /// The name of the current shader.
  /// </summary>
  string m_currentShaderName;

  /// <summary>
  /// The engine
  /// </summary>
  IEngine const *m_pEngine;

  const char* s_shaderDir = "../Assets/Shaders/";

};



#endif