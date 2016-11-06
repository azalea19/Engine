#include "ShaderLibrary.h"
#include "Utility.h"


static ShaderLibrary shaderLib;


void ShaderLibrary::initShaderLibrary()
{
	//Add shaders you need access to here
	//ShaderLibrary::getLib()->addShader("defaultShader", CreateVector(string("mvp")), CreateVector(string("position")));

	/*ShaderLibrary::getLib()->addShader
	(
		"textured",
		CreateVector(
			string("mvp"),
			string("modelMatrix"),
			string("normMatrix"),
			string("campos"),
			string("diffuse"),
			string("enableLighting"),
			string("enableAmbientLight"),
			string("ambientLightColorWeights"),
			string("enableDirectionalLight"),
			string("directionalLightColorWeights"),
			string("directionalLightDirection"),
			string("enablePointLight"),
			string("pointLightColorWeights"),
			string("pointLightPosition")),
		CreateVector(
			string("position"),
			string("uvIn"),
			string("normal"))
	);*/

	//ShaderLibrary::getLib()->addShader("colouredLight", CreateVector(string("mvp"), string("diffuse")), CreateVector(string("position"), string("uvIn")));
	//ShaderLibrary::getLib()->addShader("orthoShader", CreateVector(string("diffuse"), string("width"), string("height")), CreateVector(string("position"), string("uvIn")));
}

void ShaderLibrary::addShader(string name, std::vector<string> uniforms, std::vector<string> attributes)
{
	Shader* myShader = new Shader(name, name + ".vert", name + ".frag", attributes, uniforms);
	shaders.emplace(name, myShader);
}

ShaderLibrary* ShaderLibrary::getLib()
{
	return &shaderLib;
}

const Shader* ShaderLibrary::getShader(string name) const
{
	std::unordered_map<string, Shader*>::const_iterator got = shaders.find(name);
	if (got == shaders.end())
	{
		printf("Shader with name %s not found.", name.c_str());
		return nullptr;
	}
	else
		return got->second;
}

void ShaderLibrary::bindShader(string shaderName)
{
	const Shader* myShader = getShader(shaderName);

	if (myShader != NULL)
	{
		myShader->bind();
		currentShaderName = shaderName;
	}
}

void ShaderLibrary::bindDefaultShader()
{
	currentShaderName = "defaultShader";
	getShader(currentShaderName)->bind();
}

const Shader* ShaderLibrary::currentShader()
{
	return getShader(currentShaderName);
}

const string ShaderLibrary::getCurrentShaderName()
{
	return currentShaderName;
}