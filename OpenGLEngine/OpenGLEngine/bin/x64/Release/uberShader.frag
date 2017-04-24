#version 330 
//uniform sampler2D diffuse;

in vec2 UV;
in vec3 NORM;
in vec3 WORLDPOS;

out vec4 color; 

void main() 
{ 
	color = vec4(NORM * 0.5 + vec3(0.5, 0.5, 0.5), 1);
}; 

