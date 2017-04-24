#version 330
in vec3 position;
in vec2 uv;
in vec3 normal;
uniform mat4 mvp;
uniform mat4 modelMatrix;

out vec2 UV;
out vec3 NORM;
out vec3 WORLDPOS;

void main()
{
	UV = uv;
	NORM = normal;
	WORLDPOS = (modelMatrix * vec4(position, 1)).xyz;
	gl_Position = mvp * vec4( position, 1 );
}