#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D ourTex;

void main()
{
	FragColor = texture(ourTex, TexCoord);
}