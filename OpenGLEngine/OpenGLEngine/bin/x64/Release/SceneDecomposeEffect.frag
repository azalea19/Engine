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


layout (location = 0) uniform sampler2D ALPHA_MAP;
layout (location = 1) uniform sampler2D DIFFUSE_MAP0;
layout (location = 2) uniform sampler2D DIFFUSE_MAP1;
layout (location = 3) uniform sampler2D DIFFUSE_MAP2;
layout (location = 4) uniform sampler2D DIFFUSE_MAP3;

//DIFFUSE
uniform int DIFFUSE_SOURCE = 0;
uniform vec4 MESH_COLOUR = vec4(1, 1, 1, 1);
uniform int DIFFUSE_COUNT = 1;
uniform int zeroNormals;

//ALPHA
uniform int USE_ALPHA_MAP = 0;

float logb(float value, float base)
{
	return log(value) / log(base);
}

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
			return texture(DIFFUSE_MAP0, FRAG_DIFFUSE_COORD);
		case 3:
		{
			//Terrain multi texturing
			vec3 pos = FRAG_WORLD_POS / 32;
			vec3 tv;

			vec2 uv1 = vec2(pos.x, pos.y);
			vec2 uv2 = vec2(pos.x, pos.z);
			vec2 uv3 = vec2(pos.z, pos.y);
			tv.x = abs(normalize(FRAG_VERTEX_NORMAL).z);
			tv.y = abs(normalize(FRAG_VERTEX_NORMAL).y);
			tv.z = abs(normalize(FRAG_VERTEX_NORMAL).x);
			float tt = tv.x + tv.y + tv.z;
			tv /= tt;

			vec4 grass1 = texture(DIFFUSE_MAP0, uv1);
			vec4 grass2 = texture(DIFFUSE_MAP0, uv2);
			vec4 grass3 = texture(DIFFUSE_MAP0, uv3);
			vec4 grass = grass1 * tv.x + grass2 * tv.y + grass3 * tv.z;
			vec4 stone1 = texture(DIFFUSE_MAP1, uv1);
			vec4 stone2 = texture(DIFFUSE_MAP1, uv2);
			vec4 stone3 = texture(DIFFUSE_MAP1, uv3);
			vec4 stone = stone1 * tv.x + stone2 * tv.y + stone3 * tv.z;
			vec4 detailgrass1 = texture(DIFFUSE_MAP3, uv1 * 6.25);
			vec4 detailgrass2 = texture(DIFFUSE_MAP3, uv2 * 6.25);
			vec4 detailgrass3 = texture(DIFFUSE_MAP3, uv3 * 6.25);
			vec4 detailgrass = detailgrass1 * tv.x + detailgrass2 * tv.y + detailgrass3 * tv.z;
			vec4 detailstone1 = texture(DIFFUSE_MAP2, uv1 * 6.25);
			vec4 detailstone2 = texture(DIFFUSE_MAP2, uv2 * 6.25);
			vec4 detailstone3 = texture(DIFFUSE_MAP2, uv3 * 6.25);
			vec4 detailstone = detailstone1 * tv.x + detailstone2 * tv.y + detailstone3 * tv.z;

			float slope = abs(dot(normalize(FRAG_VERTEX_NORMAL), vec3(0, 1, 0)));
			slope = slope * slope;
			float distance = clamp(logb(FRAG_LINEAR_DEPTH / 30,2), 0, 1);
			vec4 grassColor = mix(detailgrass, grass, distance);
			vec4 stoneColor = mix(detailstone, stone, distance);
			vec4 result = mix(grassColor, stoneColor, slope);

			return result;
			//return vec4(tv, 1);
		}
			
	}
}

vec3 CalculateNormal()
{
	if(zeroNormals == 0)
	{
		return vec3(0,0,0);
	}
	return (normalize(FRAG_VERTEX_NORMAL) + vec3(1, 1, 1)) * 0.5;	
}

vec3 CalculateWorldPos()
{
	return FRAG_WORLD_POS;
}

vec3 CalculateLinearDepth()
{
	if(zeroNormals == 0)
	{
		return vec3(0,0,0);
	}
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
	
	NORMAL = CalculateNormal();
	WORLD_POS = CalculateWorldPos();
	LINEAR_DEPTH = CalculateLinearDepth();
	COLOUR = CalculateDiffuse();
}
