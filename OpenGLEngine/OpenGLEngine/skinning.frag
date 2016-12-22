#version 330

uniform sampler2D diffuse;

in vec2 TexCoord0;
in vec3 Normal0;                                                                   
in vec3 WorldPos0;
in vec4 color;   
in float val;                                                                                                        
                            
layout (location = 0) out vec4 FragColor;
                                                                
void main()
{                                                                                                                                                                                                
	FragColor = vec4(texture(diffuse, TexCoord0).xyz * 3.0, 1.0);   
}
