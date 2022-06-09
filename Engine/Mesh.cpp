#include "Mesh.h"

std::vector<float> Engine::Mesh::importModel(std::filesystem::path path)
{
	std::vector<float> vertices;
	std::ifstream file(path);
	if (!file.is_open())
		throw std::exception("File not found or cannot be opened");

	if (deserialize(file, vertices))
		return vertices;
	else throw std::exception("Unable to import model");
}

void Engine::Mesh::assemble(std::vector<float> vertices)
{
	glGenVertexArrays(1, &this->VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexArrayAttrib(this->VAO, 0);
	glEnableVertexArrayAttrib(this->VAO, 1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

Engine::Mesh::Mesh(std::filesystem::path path)
{
	std::vector<float> vertices = Mesh::importModel(path);
	this->assemble(vertices);

	this->count = vertices.size() / 5;
}

Engine::Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &this->VAO);
}

void Engine::Mesh::draw(gltk::Shader& shader) const
{
	Renderer::render(this->VAO, count);
}
