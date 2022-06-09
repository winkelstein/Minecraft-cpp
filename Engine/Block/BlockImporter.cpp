#include "BlockImporter.h"

Engine::BlockImporter::BlockImporter(Asset& asset)
{
	Engine::Model model({ asset.get<std::shared_ptr<Mesh>>("cube") });
	blocks["grass"] = new Block(Block::BlockType::Grass, model, asset.get<std::shared_ptr<gltk::Texture>>("grass"));
}

const Engine::Block& Engine::BlockImporter::get(std::string name)
{
	return *blocks[name];
}
