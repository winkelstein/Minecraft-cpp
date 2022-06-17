#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>

Engine::Model::Model(std::vector<std::shared_ptr<const Mesh>> meshes) : meshes(meshes)
{
	this->model = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, -1.0f));
}

void Engine::Model::draw(gltk::Shader& shader) const
{
	shader.bind();
	shader.uniform<glm::mat4>("model", this->model);
	for (auto& mesh : this->meshes)
		mesh->draw(shader);
}

void Engine::Model::position(glm::vec3 pos)
{
	this->model = glm::translate(glm::mat4(1.0), pos);
}
