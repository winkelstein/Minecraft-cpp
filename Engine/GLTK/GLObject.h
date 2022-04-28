#pragma once
#include <GL/glew.h>

namespace Engine
{
	namespace gltk
	{
		class glObject
		{
		protected:
			GLuint handler;

		public:
			virtual void bind() const = 0;
			virtual void unbind() const = 0;
		};
	}
}