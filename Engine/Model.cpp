#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>

template<typename POD>
static std::istream& deserialize(std::istream& is, std::vector<POD>& v)
{
	static_assert(std::is_trivial<POD>::value && std::is_standard_layout<POD>::value,
		"Can only deserialize POD types with this function");

	decltype(v.size()) size;
	is.read(reinterpret_cast<char*>(&size), sizeof(size));
	v.resize(size);
	is.read(reinterpret_cast<char*>(v.data()), v.size() * sizeof(POD));
	return is;
}

std::vector<float> Engine::Model::importModel(std::filesystem::path path)
{
	std::vector<float> vertices;
	std::ifstream file(path);
	if (!file.is_open())
		throw std::exception("File not found or cannot be opened");

	if (deserialize(file, vertices))
		return vertices;
	else throw std::exception("Unable to import model");
}

void Engine::Model::assemble(std::vector<float> vertices)
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
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
}

Engine::Model::Model(std::filesystem::path path)
{
	this->model = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, -1.0f));
	std::vector<float> vertices = Model::importModel(path);
	this->assemble(vertices);

	this->count = vertices.size() / 5;
}

Engine::Model::~Model()
{
	glDeleteVertexArrays(1, &this->VAO);
}
