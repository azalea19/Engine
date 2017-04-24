#version 330
in vec3 position;
in vec3 normal;
uniform mat4 mvp;
uniform mat4 viewMatrix;

out vec3 NORM;
out float d;
out vec3 worldpos;

void LightingCalculations()
{
	NORM = normal;
	vec4 p = (viewMatrix * vec4(position, 1));
	d = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
	worldpos = position;
}


void main()
{
	LightingCalculations();
	gl_Position = mvp * vec4( position, 1 );
}