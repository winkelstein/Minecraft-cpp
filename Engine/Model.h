#pragma once
#include <filesystem>

#include "drawable.h"

namespace Engine
{
	class Model : public drawable
	{
	private:
		GLuint VAO;
		size_t count;

		glm::mat4 model;
	private:
		static std::vector<float> importModel(std::filesystem::path path);
		void assemble(std::vector<float> vertices);
	public:
		Model(std::filesystem::path path);

	public:
		void draw(gltk::Shader& shader) const override;

	public:
		void position(glm::vec3 pos);
		inline glm::vec3 position() const
		{
			return model[3];
		}
	public:
		//TODO: make rotate and other model transformation things
	};
}