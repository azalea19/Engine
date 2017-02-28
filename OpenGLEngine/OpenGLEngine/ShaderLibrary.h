#ifndef ShaderLibrary_h__
#define ShaderLibrary_h__

#include "Types.h"
#include "Shader.h"
#include <unordered_map>
#include "Singleton.h"

/**
* @file   ShaderLibrary.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The shader library.
*
* The shader library contains all of the various shaders we have access to in the program
*/

struct ShaderLibrary : Singleton<ShaderLibrary>
{

	std::unordered_map<string, Shader*> shaders; 


	void InitShaderLibrary();


	void AddShader(string const& name, std::vector<string> const& uniforms, std::vector<string> const& attributes);

	
	const Shader* GetShader(string const& name) const;

	
	void BindShader(string const& shaderName);


	void BindDefaultShader();


	const Shader* CurrentShader() const;

	
	const string GetCurrentShaderName() const;

private:

	string m_currentShaderName;
};



#endif