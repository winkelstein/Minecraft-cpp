#pragma once
#include <vector>
#include "../drawable.h"
#include "../Block/Block.h"

namespace Engine
{
	class World : public drawable
	{
	private:
		friend class WorldImporter;
	private:
		std::vector<Block> blocks;


	public:
		void push_block(Block block);
	public:
		void draw(gltk::Shader& shader) const override;
	};
}