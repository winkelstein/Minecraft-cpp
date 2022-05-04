#pragma once
#include <glm/glm.hpp>

#include "GLTK/Shader.h"
#include "Render.h"

namespace Engine
{
	class drawable
	{
	public:
		virtual void draw(gltk::Shader& shader) const = 0;
	};
}