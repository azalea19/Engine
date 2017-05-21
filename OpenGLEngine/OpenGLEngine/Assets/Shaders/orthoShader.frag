#version 330 
uniform sampler2D diffuse;
in vec2 UV;
out vec4 LFragment; 

void main() 
{ 
	LFragment = texture(diffuse, UV);
}; 