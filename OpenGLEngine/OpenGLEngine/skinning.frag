#version 330

in vec2 TexCoord0;
in vec3 Normal0;                                                                   
in vec3 WorldPos0;
in vec4 color;   
in float val;                                                                                                        
                            
out vec4 FragColor;
                                                                
void main()
{                                                                                                                                                                                                        
    //FragColor = vec4(WorldPos0.y, 1, 1, 1);  
	FragColor = color;   
}
