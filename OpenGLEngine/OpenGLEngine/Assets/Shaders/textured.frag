#version 330 
uniform sampler2D diffuse;

in vec2 UV;
out vec4 LFragment; 




/////////// Lighting /////////////

uniform int enableLighting = 1;

uniform int enableAmbientLight = 1;
uniform vec3 ambientLightColorWeights = vec3(1.0, 1.0, 1.0);

uniform int enableDirectionalLight = 1;
uniform vec3 directionalLightColorWeights = vec3(0, 0, 0);
uniform vec3 directionalLightDirection = vec3(1, -1, 1);

uniform int enablePointLight = 1;
uniform vec3 pointLightColorWeights = vec3(0, 0, 0);
uniform vec3 pointLightPosition = vec3(0, 0, 0);

in vec3 NORM;
in vec3 WORLDPOS;
uniform vec3 campos;

vec3 norm1;
vec3 norm2;
float t;

void CalculateNormals()
{
	if(enableDirectionalLight != 0 || enablePointLight != 0)
	{
		vec3 fragDir = normalize(WORLDPOS - campos);
		norm1 = normalize(NORM);
		norm2 = -norm1;
		t = dot(fragDir, normalize(NORM)) * -0.5 + 1;
	}
}

float AmbientWeight()
{
	if(enableAmbientLight != 0)
		return 1.0f;
	else
		return 0.0f;
}

float DirectionalWeight()
{
	if(enableDirectionalLight != 0)
	{
		vec3 lDir = normalize(directionalLightDirection);
		float weight1 = max(0, dot(lDir, -norm1));
		float weight2 = max(0, dot(lDir, -norm2));
		return mix(weight1, weight2, t);
	}
	else
	{
		return 0;
	}
}

float PointWeight()
{
	if(enablePointLight != 0)
	{
		vec3 lightToFrag = WORLDPOS - pointLightPosition;
		vec3 lDir = normalize(lightToFrag);
		float weight1 = max(0, dot(lDir, -norm1));
		float weight2 = max(0, dot(lDir, -norm2));
		return mix(weight1, weight2, t) / dot(lightToFrag, lightToFrag);
	}
	else
	{
		return 0;
	}
}

vec3 lightingFactors()
{
	CalculateNormals();

	vec3 ambientF = ambientLightColorWeights * AmbientWeight();
	vec3 directionalF = directionalLightColorWeights * DirectionalWeight();
	vec3 pointF = pointLightColorWeights * PointWeight();

	return ambientF + directionalF + pointF;
}

void ApplyLighting()
{
	vec3 lFactor = lightingFactors();
	LFragment.x = LFragment.x * lFactor.x;
	LFragment.y = LFragment.y * lFactor.y;
	LFragment.z = LFragment.z * lFactor.z;
}


////////////////////////////////////////////////////////

void main() 
{ 

LFragment = texture(diffuse, UV);

	gl_FragDepth = gl_FragCoord.z;
	if(LFragment.a == 0)
	{
		discard;
	}
	else
	{
		if(LFragment.a < 0.5)
		{
			gl_FragDepth = 0.9999;
		}

		if(enableLighting != 0)
		{
			ApplyLighting();
		}
	}



}; 

