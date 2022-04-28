#pragma once
#include <glm/glm.hpp>

#include "GLTK/Shader.h"

namespace Engine
{
	class drawable
	{
	protected:
		GLuint VAO;
		size_t count;

		glm::mat4 model;

	public:
		virtual void draw(gltk::Shader& shader) const = 0;
	};
}