#version 330

in vec3 position;
in vec2 uvIn;
in vec3 normal;
uniform mat4 mvp;

//Lighting
uniform int enableLighting;
uniform mat4 modelMatrix;
uniform mat4 normMatrix;
out vec3 WORLDPOS;

out vec2 UV;
out vec3 NORM;

void LightingCalculations()
{
	WORLDPOS = (modelMatrix * vec4(position, 1)).xyz;
	NORM = normalize((normMatrix * vec4(normal, 0)).xyz);
}


void main()
{
	if(enableLighting != 0)
		LightingCalculations();

	UV = uvIn;
	gl_Position = mvp * vec4( position, 1 );
}