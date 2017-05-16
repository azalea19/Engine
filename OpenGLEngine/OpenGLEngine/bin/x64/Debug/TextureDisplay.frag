#version 330

uniform sampler2D inputTex0;

in vec2 TexCoord0;                                                                                                     
                            
layout (location = 0) out vec4 color;
                                                          
void main()
{               
	color = texture(inputTex0, TexCoord0);
}
