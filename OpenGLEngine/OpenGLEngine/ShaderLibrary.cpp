#include "ShaderLibrary.h"
#include "Utility.h"
#include "IEngine.h"
#include <memory>

static ShaderLibrary shaderLib;


void ShaderLibrary::InitShaderLibrary(IEngine const *pEngine)
{
	ShaderLibrary& shaderLibrary = ShaderLibrary::GetInstance();
  shaderLibrary.m_pEngine = pEngine;

	shaderLibrary.AddShader("defaultShader", CreateVector(string("mvp")), CreateVector(string("position")));

	shaderLibrary.AddShader("orthoShader", CreateVector(string("diffuse"), string("width"), string("height")), CreateVector(string("position"), string("uvIn")));
	shaderLibrary.AddShader("SceneDecomposeEffect", CreateVector(string("zeroNormals"),string("DIFFUSE_COUNT"),string("CAMERA_POSITION"), string("WORLD_VIEW_PROJECTION_MATRIX"), string("WORLD_MATRIX"), string("VIEW_MATRIX"), string("PROJECTION_MATRIX"), string("BONES"), string("ANIMATION_ENABLED"), string("DIFFUSE_SOURCE"), string("MESH_COLOUR"), string("DIFFUSE_MAP0"),string("DIFFUSE_MAP1"), string("DIFFUSE_MAP2"), string("DIFFUSE_MAP3"), string("ALPHA_MAP"), string("USE_ALPHA_MAP")), CreateVector(string("VERT_ALPHA_COORD"), string("VERT_POSITION"), string("VERT_DIFFUSE_COORD"), string("VERT_NORMAL"), string("VERT_BONE_IDS"), string("VERT_BONE_WEIGHTS"), string("VERT_COLOUR")));
	shaderLibrary.AddShader("HDRSplitEffect", CreateVector(string("inputTex0")), CreateVector(string("Position"), string("TexCoord")));
	shaderLibrary.AddShader("BlurEffect", CreateVector(string("inputTex0"), string("blurRadius")), CreateVector(string("Position"), string("TexCoord")));
	shaderLibrary.AddShader("DirectionalLightingEffect", CreateVector(string("inputTex0"), string("inputTex1"), string("CAMERA_POSITION"), string("LIGHT_COLOUR"), string("LIGHT_DIRECTION"), string("AMBIENT_COLOUR")), CreateVector(string("Position"), string("TexCoord")));
	shaderLibrary.AddShader("AdditiveBlendEffect", CreateVector(string("inputTex0"), string("inputTex1")), CreateVector(string("Position"), string("TexCoord")));
	shaderLibrary.AddShader("MultiplicativeBlendEffect", CreateVector(string("inputTex0"), string("inputTex1")), CreateVector(string("Position"), string("TexCoord")));
	shaderLibrary.AddShader("FXAAEffect", CreateVector(string("inputTex0"), string("FXAA_SPAN")), CreateVector(string("Position"), string("TexCoord")));
	shaderLibrary.AddShader("DepthThresholdEffect", CreateVector(string("inputTex0"), string("threshold")), CreateVector(string("Position"), string("TexCoord")));
	shaderLibrary.AddShader("RayEffect", CreateVector(string("inputTex0"), string("lightPos")), CreateVector(string("Position"), string("TexCoord")));
	shaderLibrary.AddShader("TextureDisplay", CreateVector(string("inputTex0")), CreateVector(string("Position"), string("TexCoord")));
}

void ShaderLibrary::AddShader(string const& name, std::vector<string> const& uniforms, std::vector<string> const& attributes)
{
	//IShader* myShader = new Shader(name, name + ".vert", name + ".frag", attributes, uniforms);
  IShader* pShader = m_pEngine->CreateShader(name, name + ".vert", name + ".frag", attributes, uniforms);
	shaders.emplace(name, pShader);
}

std::unique_ptr<IShader> const& ShaderLibrary::GetShader(string const& name) const
{
	std::unordered_map<string, std::unique_ptr<IShader>>::const_iterator got = shaders.find(name);
	if (got == shaders.end())
	{
		printf("Shader with name %s not found.", name.c_str());
		return nullptr;
	}
	else
		return got->second;
}

void ShaderLibrary::BindShader(string const& shaderName)
{
  std::unique_ptr<IShader> const& myShader = GetShader(shaderName);

	if (myShader != NULL)
	{
		myShader->Bind();
		m_currentShaderName = shaderName;
	}
}

void ShaderLibrary::BindDefaultShader()
{
	m_currentShaderName = "defaultShader";
	GetShader(m_currentShaderName)->Bind();
}

std::unique_ptr<IShader> const& ShaderLibrary::CurrentShader() const
{
	return GetShader(m_currentShaderName);
}

string const& ShaderLibrary::GetCurrentShaderName() const
{
	return m_currentShaderName;
}