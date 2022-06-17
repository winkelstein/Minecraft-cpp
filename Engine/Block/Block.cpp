#include "Block.h"

Engine::Block::Block(BlockType id, Model model, std::shared_ptr<gltk::Texture> texture) : id(id), model(model), texture(texture)
{
}

void Engine::Block::draw(gltk::Shader& shader) const
{
	shader.bind();
	this->texture->active(0);
	this->texture->bind();
	shader.uniform("Texture", 0);
	this->model.draw(shader);
}

void Engine::Block::position(glm::vec3 position)
{
	model.position(position);
}
