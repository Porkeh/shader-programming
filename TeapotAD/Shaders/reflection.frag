#version 430


in vec3 N;
in vec3 vertPos;

uniform vec3 cameraPos;
uniform samplerCube cubeMap;
uniform mat4 V;

out vec4 colour;

void main()
{

	vec3 dir = normalize(vertPos);
	vec3 normal = normalize(N);

	vec3 reflection = reflect(dir, normal);

	reflection = vec3(inverse(V) * vec4(reflection, 0.0));

	colour = texture(cubeMap, reflection);



}
