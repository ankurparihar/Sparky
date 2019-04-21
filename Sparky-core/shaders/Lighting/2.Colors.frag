#version 330 core

out vec4 color;

uniform vec4 lightColor;
uniform vec4 objectColor;

void main()
{
	float ambientStrength = 0.1;
	vec4 ambient = ambientStrength * lightColor;

	color = ambient * objectColor;
}