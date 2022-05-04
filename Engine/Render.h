#pragma once
#include "GLTK/Shader.h"

namespace Engine
{
	class Renderer
	{
	public:
		static void render(GLuint VAO, int count)
		{
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, count);
		}
	};
}