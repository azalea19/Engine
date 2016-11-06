#ifndef ShaderLibrary_h__
#define ShaderLibrary_h__

#include "Types.h"
#include "Shader.h"
#include <unordered_map>

/**
* @file   ShaderLibrary.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The shader library.
*
* The shader library contains all of the various shaders we have access to in the program
*/

struct ShaderLibrary
{

	std::unordered_map<string, Shader*> shaders; 


	void initShaderLibrary();


	void addShader(string name, std::vector<string> uniforms, std::vector<string> attributes);

	
	const Shader* getShader(string name) const;


	static ShaderLibrary* getLib();

	
	void bindShader(string shaderName);


	void bindDefaultShader();


	const Shader* currentShader();

	
	const string getCurrentShaderName();

private:
	string currentShaderName;
};



#endif