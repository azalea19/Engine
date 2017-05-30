#version 400

in vec2 TexCoord0;
layout (location = 0) out vec3 color;

uniform sampler2D inputTex0;
uniform sampler2D inputTex1;
uniform sampler2D inverseDepthBuffer;
 
vec3 applyFog(vec3 color)
{
	vec3 fogColor = vec3(205/255.0,133/255.0,0);
	float viewDistance = 2000;
	float wsDepth = 1 / texture2D(inverseDepthBuffer, TexCoord0).x;
	float interpolationFactor = min(log(1 + wsDepth / viewDistance), 0.6);

	vec3 finalColor = mix(color,fogColor, interpolationFactor);
	
	return finalColor;
}


void main() 
{
	color = texture2D(inputTex0, TexCoord0).xyz * texture2D(inputTex1, TexCoord0).xyz;
	color = applyFog(color.xyz);
}


