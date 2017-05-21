#version 330 
out vec4 LFragment; 

in vec3 NORM;
in float d;
in vec3 worldpos;

float waterHeight = 25;
float beachHeight = 30;
vec3 deepWaterColour = vec3(10 / 255.0, 23 / 255.0, 78 / 255.0);
vec3 waterColour = vec3(77 / 255.0, 156 / 255.0, 163/255.0);
vec3 grassColour = vec3(56 / 255.0, 100 / 255.0, 51 / 255.0);
vec3 snowColour = vec3(1.0, 1.0, 1.0);
vec3 sandColour = vec3(215 / 255.0, 215 / 255.0, 129 / 255.0);

////////////////////////////////////////////////////////

float lightingFactor()
{
	vec3 lightDir = normalize(vec3(1, 1, -1));
	float l = (max(dot(-normalize(NORM), lightDir), 0) + 1) / 2;
	return l;
}

vec3 colour()
{
	float height = pow(min(1.0, ((worldpos.y - beachHeight) / 20)), 6);
	return mix(grassColour, snowColour, height);
}

vec3 waterc()
{
	return mix(deepWaterColour, waterColour, pow(worldpos.y / waterHeight, 6));
}

vec3 beachc()
{
	return mix(sandColour, grassColour, pow((worldpos.y - waterHeight) / (beachHeight - waterHeight), 6));
}

void main() 
{ 
	float l = lightingFactor();
	
	if(worldpos.y < waterHeight)
	{
		LFragment = vec4(waterc() * l, 1);
	}
	else if(worldpos.y < beachHeight)
	{
		LFragment = vec4(beachc() * l, 1);
	}
	else
	{
		LFragment = vec4(colour() * l, 1);
	}	

}; 

