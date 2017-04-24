#version 330

in vec3 position;
in vec2 uvIn;

uniform int width = 1280;
uniform int height = 720;

out vec2 UV;

void main()
{
	vec3 newpos = position;
	newpos.x = ((position.x/width) - 0.5) * 2;
	newpos.y = ((position.y/height) - 0.5) * -2;
	newpos.z = 0.5;

	UV = uvIn;
	gl_Position = vec4( newpos, 1 );
}