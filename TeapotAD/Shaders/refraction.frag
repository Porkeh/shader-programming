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
	float ratio = 1.0/1.333;

	vec3 refraction = refract(dir, normal, ratio);

	refraction = vec3(inverse(V) * vec4(refraction, 0.0));

	colour = texture(cubeMap, refraction);



}
