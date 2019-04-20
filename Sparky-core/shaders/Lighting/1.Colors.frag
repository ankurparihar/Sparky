#version 330 core

out vec4 color;

uniform vec4 lightColor;
uniform vec4 objectColor;

void main()
{
	color = lightColor * objectColor;
}