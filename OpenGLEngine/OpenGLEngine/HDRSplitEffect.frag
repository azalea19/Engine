#version 330

uniform sampler2D inputTex0;

in vec2 TexCoord0;                                                                                                     
                            
layout (location = 0) out vec4 lowColor;
layout (location = 1) out vec4 highColor;

vec4 GetLowColor(vec4 colorIn)
{
	vec4 result;
	result.x = min(colorIn.x, 1);
	result.y = min(colorIn.y, 1);
	result.z = min(colorIn.z, 1);
	result.w = 1;
	return result;
}

vec4 GetHighColor(vec4 colorIn)
{
	//vec3 result = vec3(0, 0, 0);
	//if(colorIn.x + colorIn.y + colorIn.z > 3)
	//{
	//	result += colorIn.xyz;
	//}
	//return vec4(result, 1);

	vec4 result;
	result.x = max(colorIn.x - 1, 0);
	result.y = max(colorIn.y - 1, 0);
	result.z = max(colorIn.z - 1, 0);
	result.w = 1;
	return result;
}
                                                                
void main()
{               
	vec4 colorIn = texture(inputTex0, TexCoord0);
	lowColor = GetLowColor(colorIn);
	highColor = GetHighColor(colorIn);
}
