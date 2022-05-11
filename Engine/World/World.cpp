#include "World.h"

void Engine::World::push_block(Block block)
{
	this->blocks.push_back(block);
}

void Engine::World::draw(gltk::Shader& shader) const
{
	for (auto& el : blocks)
		el.draw(shader);
}
