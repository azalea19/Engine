#version 430

in vec2 TexCoord0;
layout (location = 0) out vec3 COLOR;

layout (location = 0) uniform sampler2D inputTex0;
 
 uniform vec3 LIGHT_COLOUR = vec3(1, 1, 1);
 uniform vec3 LIGHT_DIRECTION = vec3(1, -1, 1);
 uniform vec3 AMBIENT_COLOUR = vec3(0.5, 0.5, 0.5);

void main() 
{
	vec3 normal = (texture2D(inputTex0, TexCoord0).xyz * 2) - 1;

	if(normal == vec3(-1,-1,-1))
	{
		COLOR = vec3(1,1,1);
	}
	else
	{
		float l = dot(LIGHT_DIRECTION, normalize(-normal));
		l = max(0, l);
		COLOR = l * LIGHT_COLOUR + AMBIENT_COLOUR;
	}	
}


