#pragma once
#include <exception>
#include <Windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>

/* glContext creating an OpenGL context of your window for enable OpenGl functions */
namespace Engine
{
	namespace gltk
	{
		namespace _glContext
		{
			class glContext
			{
			private:
				HDC hdc;
				HGLRC context;

			public:
				virtual ~glContext();

				void makeContextCurrent() const;
				void swapBuffers() const;

				void clear() const;
				void clearColor(float red, float green, float blue, float alpha) const;

			protected:
				void createContext(HWND window_handler);
			};
		}
	}
}