#include "Screen.h"

Engine::Screen::Screen(const WS::Size size)
{
	glViewport(0, 0, size.width, size.height);
	memset(&this->mvp, 0, sizeof(MVP));
	this->mvp.projection = glm::perspectiveFov(glm::radians(60.0f), (float)size.width, (float)size.height, 0.01f, 100.0f);

	this->ubo.bind();
	this->ubo.bindBase(0);

	this->ubo.data(&this->mvp);
}

void Engine::Screen::render()
{
	std::lock_guard lock(this->mtx);
	this->ubo.bind();
	this->ubo.data(&this->mvp);

	while (!this->qDraw.empty())
	{
		this->qDraw.front().first->draw(this->qDraw.front().second);
		this->qDraw.pop();
	}
}

void Engine::Screen::push(const drawable* object, gltk::Shader& shader)
{
	std::lock_guard lock(this->mtx);
	this->qDraw.push(std::pair<const drawable*, gltk::Shader&>(object, shader));
}

void Engine::Screen::resize(const WS::Size size)
{
	if ((size.width && size.height) > 0)
	{
		glViewport(0, 0, size.width, size.height);
		this->mvp.projection = glm::perspectiveFov(glm::radians(60.0f), (float)size.width, (float)size.height, 0.01f, 100.0f);
	}
}

void Engine::Screen::onUpdateCamera(const Camera& cam)
{
	this->mvp.camera_view = cam.view();
}
