#version 430

in vec3 tex;

out vec4 colour;

uniform samplerCube skybox;

void main()
{
	colour = texture(skybox,tex);
}