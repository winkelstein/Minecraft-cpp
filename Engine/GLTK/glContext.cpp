#include "glContext.h"

Engine::gltk::_glContext::glContext::~glContext()
{
	wglDeleteContext(this->context);
}

void Engine::gltk::_glContext::glContext::makeContextCurrent()
{
	wglMakeCurrent(this->hdc, this->context);
}

void Engine::gltk::_glContext::glContext::swapBuffers()
{
	SwapBuffers(this->hdc);
}

void Engine::gltk::_glContext::glContext::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::gltk::_glContext::glContext::clearColor(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
}

void Engine::gltk::_glContext::glContext::createContext(HWND window_handler)
{
	PIXELFORMATDESCRIPTOR pd;
	memset(&pd, 0, sizeof(pd));
	pd.nSize = sizeof(pd);
	pd.nVersion = 1;
	pd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pd.iPixelType = PFD_TYPE_RGBA;
	pd.cColorBits = 32;
	pd.cDepthBits = 24;
	pd.cStencilBits = 8;
	pd.iLayerType = PFD_MAIN_PLANE;

	this->hdc = GetWindowDC(window_handler);

	int pixelformat = ChoosePixelFormat(this->hdc, &pd);
	SetPixelFormat(this->hdc, pixelformat, &pd);

	//Create temp OpenGL context to load OpenGL functions from Opengl32.dll and then create better context
	HGLRC temp = wglCreateContext(this->hdc);
	wglMakeCurrent(this->hdc, temp);

	glewExperimental = true;

	if (glewInit() != GLEW_OK)
		throw std::exception("Unable to initialize GLEW");

	int attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,
		WGL_CONTEXT_FLAGS_ARB, 3,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	int pixelformatattriblist[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, true,
		WGL_SUPPORT_OPENGL_ARB, true,
		WGL_DOUBLE_BUFFER_ARB, true,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		WGL_SAMPLE_BUFFERS_ARB, 1,
		WGL_SAMPLES_ARB, 8,
		0
	};

	if (wglewInit() != GLEW_OK)
		throw std::exception("Unable to initialize WGLEW");

	//Create better context
	UINT numFormats;
	wglChoosePixelFormatARB(this->hdc, pixelformatattriblist, NULL, 1, &pixelformat, &numFormats);
	this->context = wglCreateContextAttribsARB(this->hdc, 0, attribs);

	if (numFormats == 0)
		throw std::exception("Unable to set custom pixel format");

	wglDeleteContext(temp);

	this->makeContextCurrent();
}
