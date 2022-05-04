#include "Block.h"

Engine::Block::Block(BlockType id, Model model) : id(id), model(model)
{
}

void Engine::Block::draw(gltk::Shader& shader) const
{
	this->model.draw(shader);
}

void Engine::Block::position(glm::vec3 position)
{
	model.position(position);
}
