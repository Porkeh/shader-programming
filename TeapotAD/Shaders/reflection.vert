#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 N;
out vec3 vertPos;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{
	
	gl_Position = P *V * M * vec4(VertexPosition, 1.0);
	N = vec3(V * M * vec4(VertexNormal, 0.0));
	vertPos = vec3( V * M * vec4(VertexPosition, 1.0));

}