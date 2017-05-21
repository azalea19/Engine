#version 400

in vec2 TexCoord0;
layout (location = 0) out vec3 color;

uniform sampler2D inputTex0;
uniform sampler2D inputTex1;
 
void main() 
{
	color = texture2D(inputTex0, TexCoord0).xyz * texture2D(inputTex1, TexCoord0).xyz;
}


