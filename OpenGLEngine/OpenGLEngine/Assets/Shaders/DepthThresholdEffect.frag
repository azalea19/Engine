#version 400

in vec2 TexCoord0;
layout (location = 0) out vec3 color;

uniform sampler2D inputTex0;

//distance to the light from the camera
uniform float threshold;
vec3 bgColor = vec3(1, 1, 1);
 
void main() 
{
	
    float inverseDepth = texture(inputTex0,TexCoord0).r;
	if(inverseDepth == 0)
	{
		color = bgColor;
	} 
	else
	{
		float depth = 1/inverseDepth;
		if(depth > threshold)
		{
			color = bgColor;
		}
		else
		{
			color = vec3(0,0,0);
		}
	}
}


