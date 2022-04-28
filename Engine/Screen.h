#pragma once
#include <queue>
#include <mutex>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "drawable.h"
#include "WS/Core.h"
#include "GLTK/UniformBuffer.h"
#include "GLTK/Shader.h"

namespace Engine
{
	struct MVP
	{
		glm::mat4 projection;
		glm::mat4 camera_view;
	};

	class Screen
	{
	private:
		gltk::UniformBuffer<MVP> ubo;
		MVP mvp;

		std::queue<std::pair<const drawable*, gltk::Shader&>> qDraw;
		std::recursive_mutex mtx;

	public:
		Screen(const WS::Size size);

	public:

		void render();
		void push(const drawable* object, gltk::Shader& shader);

	public:
		void resize(const WS::Size size);
		void onUpdateCamera(const Camera& cam);
	};
}