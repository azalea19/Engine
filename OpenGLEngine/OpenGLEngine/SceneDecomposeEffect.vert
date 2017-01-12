#version 330                                                                        

const int MAX_BONES = 100;
                                                                                
layout (location = 0) in vec3 VERT_POSITION;                                             
layout (location = 1) in vec2 VERT_DIFFUSE_COORD; 
layout (location = 2) in vec2 VERT_ALPHA_COORD;                                            
layout (location = 3) in vec3 VERT_NORMAL;                                               
layout (location = 4) in ivec4 VERT_BONE_IDS;
layout (location = 5) in vec4 VERT_BONE_WEIGHTS;
layout (location = 6) in vec4 VERT_COLOUR;

out vec2 FRAG_DIFFUSE_COORD;
out vec2 FRAG_ALPHA_COORD;
out vec3 FRAG_VERTEX_NORMAL;
out vec4 FRAG_VERTEX_COLOUR;
out vec3 FRAG_WORLD_POS;                                                                
out float FRAG_LINEAR_DEPTH;


uniform mat4 WORLD_VIEW_PROJECTION_MATRIX;
uniform mat4 WORLD_MATRIX;
uniform mat4 VIEW_MATRIX;
uniform mat4 PROJECTION_MATRIX;
uniform vec3 CAMERA_POSITION;

//DIFFUSE
uniform int DIFFUSE_SOURCE = 0;
//ALPHA
uniform int USE_ALPHA_MAP = 0;

void CalculateDiffuse()
{
	switch(DIFFUSE_SOURCE)
	{
		case 0:
			break;
		case 1:
			FRAG_VERTEX_COLOUR = VERT_COLOUR;
			break;
		case 2:
			FRAG_DIFFUSE_COORD = VERT_DIFFUSE_COORD;
			break;
	}
}

void CalculateAlpha()
{
	FRAG_ALPHA_COORD = VERT_ALPHA_COORD;
}

//ANIMATION
uniform int ANIMATION_ENABLED = 0;
uniform mat4 BONES[MAX_BONES];
mat4 boneTransform = mat4(1.0);

void CalculateBoneTransform()
{
	if(ANIMATION_ENABLED == 1)
	{
		boneTransform = BONES[VERT_BONE_IDS[0]] * VERT_BONE_WEIGHTS[0];
		boneTransform += BONES[VERT_BONE_IDS[1]] * VERT_BONE_WEIGHTS[1];
		boneTransform += BONES[VERT_BONE_IDS[2]] * VERT_BONE_WEIGHTS[2];
		boneTransform += BONES[VERT_BONE_IDS[3]] * VERT_BONE_WEIGHTS[3];
	}
}

void CalculateWorldPosAndProjection()
{
	vec3 animated = (boneTransform * vec4(VERT_POSITION, 1.0)).xyz;
	FRAG_WORLD_POS = (WORLD_MATRIX * vec4(animated, 1.0)).xyz;
	gl_Position = WORLD_VIEW_PROJECTION_MATRIX * vec4(animated, 1.0);
}

void CalculateNormal()
{
	mat4 normMatrix = WORLD_MATRIX * boneTransform;
	normMatrix = transpose(inverse(normMatrix));
	FRAG_VERTEX_NORMAL = normalize((normMatrix * vec4(VERT_NORMAL, 0)).xyz);
}

void CalculateLinearDepth()
{
	vec3 vc = CAMERA_POSITION - FRAG_WORLD_POS;
	FRAG_LINEAR_DEPTH = sqrt(vc.x*vc.x + vc.y*vc.y + vc.z*vc.z);
}

void main()
{
	CalculateBoneTransform();

	CalculateWorldPosAndProjection();

	CalculateNormal();

	CalculateDiffuse();    
	
	CalculateLinearDepth();    
	
	CalculateAlpha();   
}
