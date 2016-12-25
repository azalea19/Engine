#version 330                                                                        
                                                                                    
layout (location = 0) in vec3 Position;                                             
layout (location = 1) in vec2 TexCoord;                                             
layout (location = 2) in vec3 Normal;                                               
layout (location = 3) in ivec4 BoneIDs;
layout (location = 4) in vec4 Weights;
layout (location = 5) in vec4 Colour;

out vec2 TexCoord0;
out vec3 Normal0;                                                                   

const int MAX_BONES = 100;

uniform mat4 mvp;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

//DIFFUSE
uniform int DIFFUSE_SOURCE = 0;
out vec4 VERTEX_COLOUR;

void ApplyDiffuse()
{
	switch(DIFFUSE_SOURCE)
	{
		case 0:
			break;
		case 1:
		VERTEX_COLOUR = Colour;
			break;
		case 2:
			TexCoord0 = TexCoord;
			break;
			
	}
}


//ANIMATION
uniform int ANIMATION_ENABLED = 0;
uniform mat4 BONES[MAX_BONES];

void ApplyAnimation()
{
	if(ANIMATION_ENABLED == 1)
	{
		mat4 BoneTransform = BONES[BoneIDs[0]] * Weights[0];
		BoneTransform     += BONES[BoneIDs[1]] * Weights[1];
		BoneTransform     += BONES[BoneIDs[2]] * Weights[2];
		BoneTransform     += BONES[BoneIDs[3]] * Weights[3];
		gl_Position = vec4((BoneTransform * gl_Position).xyz, 1.0);
		Normal0 = normalize((BoneTransform, vec4(Normal0, 0)).xyz);
	}
}



void ApplyMVP()
{
	gl_Position = mvp * gl_Position;
	Normal0 = (modelMatrix * vec4(Normal0, 0)).xyz;
}

void Initialize()
{
	gl_Position = vec4(Position, 1.0);
	Normal0 = Normal;
}

void main()
{
	Initialize();

	ApplyAnimation();

	ApplyMVP();

	ApplyDiffuse();             
}
