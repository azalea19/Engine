#version 400

in vec2 TexCoord0;
layout (location = 0) out vec3 color;

uniform sampler2D inputTex0;
uniform sampler2D inputTex1;

vec3 ToneMap(vec3 x)
{
	return x;
	//float A = 0.15;
	//float B = 0.50;
	//float C = 0.10;
	//float D = 0.20;
	//float E = 0.02;
	//float F = 0.30;
	//
    //return ((x*(A*x+C*B)+D*E)/(x*(A*x+B)+D*F))-E/F;
}
 
void main() 
{
    vec3 tempcolor = ToneMap((texture2D(inputTex0, TexCoord0).xyz + texture2D(inputTex1, TexCoord0).xyz));
	color = tempcolor;
}


