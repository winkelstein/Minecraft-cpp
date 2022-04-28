#pragma once
#include <string>

#include "Camera.h"
#include "WS/Event.h"
#include "WS/Mouse.h"
#include "WS/Keyboard.h"

#define TICK_COEFF 120

namespace Engine
{
	class Player 
	{
	private:
		std::string nickname;

	private:
		Camera m_camera;

		float speed;
		bool inJump;
		glm::vec3 acceleration;

		float sensetive;

	private:
		void move(glm::vec3 acc);

	public:
		Player(std::string nickname);

	public:
		void onMouseInput(const Engine::WS::Event& ev);
		void onKeyboardInput(const Engine::WS::Event& ev);

		void process(double ticks);

	public:
		inline const Engine::Camera& camera() const { return this->m_camera; }
	};
}