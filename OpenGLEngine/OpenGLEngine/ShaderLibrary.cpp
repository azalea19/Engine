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
	ShaderLibrary::getLib()->addShader("orthoShader", CreateVector(string("diffuse"), string("width"), string("height")), CreateVector(string("position"), string("uvIn")));
  ShaderLibrary::getLib()->addShader("SceneDecomposeEffect", CreateVector(string("CAMERA_POSITION"), string("WORLD_VIEW_PROJECTION_MATRIX"), string("WORLD_MATRIX"), string("VIEW_MATRIX"), string("PROJECTION_MATRIX"), string("BONES"), string("ANIMATION_ENABLED"), string("DIFFUSE_SOURCE"), string("MESH_COLOUR"), string("DIFFUSE_MAP"), string("ALPHA_MAP"), string("USE_ALPHA_MAP")), CreateVector(string("VERT_ALPHA_COORD"), string("VERT_POSITION"), string("VERT_DIFFUSE_COORD"), string("VERT_NORMAL"), string("VERT_BONE_IDS"), string("VERT_BONE_WEIGHTS"), string("VERT_COLOUR")));
  ShaderLibrary::getLib()->addShader("HDRSplitEffect", CreateVector(string("inputTex0")), CreateVector(string("Position"), string("TexCoord")));
  ShaderLibrary::getLib()->addShader("BlurEffect", CreateVector(string("inputTex0"), string("blurRadius")), CreateVector(string("Position"), string("TexCoord")));
  ShaderLibrary::getLib()->addShader("DirectionalLightingEffect", CreateVector(string("inputTex0"), string("inputTex1"), string("CAMERA_POSITION"), string("LIGHT_COLOUR"), string("LIGHT_DIRECTION"), string("AMBIENT_COLOUR")), CreateVector(string("Position"), string("TexCoord")));
  ShaderLibrary::getLib()->addShader("AdditiveBlendEffect", CreateVector(string("inputTex0"), string("inputTex1")), CreateVector(string("Position"), string("TexCoord")));
  ShaderLibrary::getLib()->addShader("MultiplicativeBlendEffect", CreateVector(string("inputTex0"), string("inputTex1")), CreateVector(string("Position"), string("TexCoord")));
  ShaderLibrary::getLib()->addShader("FXAAEffect", CreateVector(string("inputTex0"), string("FXAA_SPAN")), CreateVector(string("Position"), string("TexCoord")));
  ShaderLibrary::getLib()->addShader("DepthThresholdEffect", CreateVector(string("inputTex0"), string("threshold")), CreateVector(string("Position"), string("TexCoord")));
  ShaderLibrary::getLib()->addShader("RayEffect", CreateVector(string("inputTex0"), string("lightPos")), CreateVector(string("Position"), string("TexCoord")));
  ShaderLibrary::getLib()->addShader("TextureDisplay", CreateVector(string("inputTex0")), CreateVector(string("Position"), string("TexCoord")));
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