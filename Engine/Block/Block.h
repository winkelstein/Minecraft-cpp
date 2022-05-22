#pragma once
#include "../Model.h"
#include "../GLTK/Texture.h"
#include "../drawable.h"

namespace Engine
{
	class Block : public drawable
	{
	public:
		enum class BlockType
		{
			Air, Grass
		};

	private:
		Model model;
		gltk::Texture texture;
		BlockType id;
		
	private:
		friend class BlockImporter;
		Block(BlockType id, Model model, gltk::Texture texture);

	public:
		void draw(gltk::Shader& shader) const override;

	public:
		void position(glm::vec3 position);
		inline glm::vec3 position() const
		{
			return model.position();
		}
	};
}