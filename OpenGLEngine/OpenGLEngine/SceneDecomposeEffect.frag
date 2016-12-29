#version 430

layout (location = 0) out vec4 COLOUR;
layout (location = 1) out vec3 NORMAL;
layout (location = 2) out vec3 WORLD_POS;
layout (location = 3) out vec3 LINEAR_DEPTH;

in vec2 FRAG_DIFFUSE_COORD;
in vec2 FRAG_ALPHA_COORD;
in vec3 FRAG_WORLD_POS;
in vec3 FRAG_VERTEX_NORMAL;
in vec4 FRAG_VERTEX_COLOUR;
in float FRAG_LINEAR_DEPTH;

layout (location = 0) uniform sampler2D DIFFUSE_MAP;
layout (location = 1) uniform sampler2D ALPHA_MAP;

//DIFFUSE
uniform int DIFFUSE_SOURCE = 0;
uniform vec4 MESH_COLOUR = vec4(1, 1, 1, 1);

//ALPHA
uniform int USE_ALPHA_MAP = 0;

vec4 CalculateDiffuse()
{
	//Mesh Colour
	switch(DIFFUSE_SOURCE)
	{
		case 0:
			return MESH_COLOUR;
		
		case 1:
			return FRAG_VERTEX_COLOUR;

		case 2:
			return texture(DIFFUSE_MAP, FRAG_DIFFUSE_COORD);
	}
}

vec3 CalculateNormal()
{
	return (normalize(FRAG_VERTEX_NORMAL) + vec3(1, 1, 1)) * 0.5;
}

vec3 CalculateWorldPos()
{
	return FRAG_WORLD_POS;
}

vec3 CalculateLinearDepth()
{
	return vec3(1/FRAG_LINEAR_DEPTH, 1/FRAG_LINEAR_DEPTH, 1/FRAG_LINEAR_DEPTH);
}

float CalculateAlpha()
{
	if(USE_ALPHA_MAP == 1)
	{
		return texture2D(ALPHA_MAP, FRAG_ALPHA_COORD).x;
	}
	else
	{
		return 1;
	}
}
                                                              
void main()
{
	if(CalculateAlpha() <= 0.8)
	{
		discard;
		return;
	}
	
	COLOUR = CalculateDiffuse();
	NORMAL = CalculateNormal();
	WORLD_POS = CalculateWorldPos();
	LINEAR_DEPTH = CalculateLinearDepth();
}
