#pragma once
#include "GLTK/Shader.h"

namespace Engine
{
	class Render
	{
	public:
		virtual void render(GLuint VAO, size_t count) const
		{
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, count);
		}
	};
}