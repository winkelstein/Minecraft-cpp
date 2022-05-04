#pragma once
#include "../Model.h"
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
		BlockType id;
		
	private:
		friend class BlockImporter;
		Block(BlockType id, Model model);

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