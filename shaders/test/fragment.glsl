#version 460 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D Texture;

void main()
{
	FragColor = texture(Texture, TexCoords);
}