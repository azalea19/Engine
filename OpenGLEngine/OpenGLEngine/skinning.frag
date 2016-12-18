#version 330

uniform sampler2D diffuse;

in vec2 TexCoord0;
in vec3 Normal0;                                                                   
in vec3 WorldPos0;
in vec4 color;   
in float val;                                                                                                        
                            
out vec4 FragColor;
                                                                
void main()
{                                                                                                                                                                                                         
	FragColor = texture(diffuse, TexCoord0);   
}
