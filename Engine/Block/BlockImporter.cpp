#include "BlockImporter.h"

Engine::BlockImporter::BlockImporter(Asset& asset)
{
	blocks["grass"] = new Block(Block::BlockType::Grass, asset.get<Model>("cube"), asset.get<gltk::Texture>("grass"));
}

const Engine::Block& Engine::BlockImporter::get(std::string name)
{
	return *blocks[name];
}
