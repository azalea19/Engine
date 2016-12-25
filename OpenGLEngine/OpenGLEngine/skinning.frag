#version 330



in vec2 TexCoord0;
in vec3 Normal0;                                                                   
in vec3 WorldPos0;
in vec4 color;   
in float val;                                                                                                        
                            
layout (location = 0) out vec4 FragColor;


//DIFFUSE
uniform int DIFFUSE_SOURCE = 0;
uniform vec4 MESH_COLOUR = vec4(1, 1, 1, 1);
in vec4 VERTEX_COLOUR;
uniform sampler2D DIFFUSE_TEXTURE;

void ApplyDiffuse()
{
	//Mesh Colour
	switch(DIFFUSE_SOURCE)
	{
		case 0:
			FragColor = MESH_COLOUR;
			break;
		
		case 1:
			FragColor = VERTEX_COLOUR;
			break;

		case 2:
			FragColor = texture(DIFFUSE_TEXTURE, TexCoord0);
			break;
	}
}
                                                                
void main()
{
	ApplyDiffuse();  
}
