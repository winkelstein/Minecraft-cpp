#pragma once
#include <unordered_map>

#include "Block.h"
#include "../Asset.h"

namespace Engine
{
	class BlockImporter
	{
		std::unordered_map<std::string, Block*> blocks;
	public:
		BlockImporter(Asset& asset);

	public:
		const Block& get(std::string name);
	};
}