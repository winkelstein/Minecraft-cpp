#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoords;

layout (binding = 0) uniform mvp
{
	mat4 proj;
	mat4 view;
};

uniform mat4 model;

out vec2 TexCoords;

void main()
{
	TexCoords = texcoords;
	gl_Position = proj * view * model * vec4(position, 1.0);
}