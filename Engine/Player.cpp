#include "Player.h"

void Engine::Player::move(glm::vec3 acc)
{
	glm::vec3 position = this->m_camera.position();
	glm::vec3 front = this->m_camera.front();

	front.y = 0.0;

	position += glm::normalize(front) * acc.x;
	position += glm::normalize(glm::cross(front, glm::vec3(0.0, 1.0, 0.0))) * acc.z;
	position += glm::normalize(glm::cross(front, glm::cross(front, glm::vec3(0.0, 1.0, 0.0)))) * (-acc.y);

	this->m_camera.position(position);
}

Engine::Player::Player(std::string nickname) : nickname(nickname), speed(1.3), sensetive(0.1), inJump(false), acceleration(glm::vec3(0.0))
{
}

void Engine::Player::onMouseInput(const Engine::WS::Event& ev)
{
	using Engine::WS::Mouse;

	static float pitch, yaw;

	float xoff = ((int64_t)Mouse::position(*ev.window()).x - (int64_t)(ev.window()->size().width / 2.0));
	float yoff = ((int64_t)(ev.window()->size().height / 2.0) - (int64_t)Mouse::position(*ev.window()).y);

	yaw += xoff * this->sensetive;
	pitch += yoff * this->sensetive;

	if (pitch > 85.0) pitch = 85.0;
	else if (pitch < -85.0) pitch = -85.0;

	this->m_camera.rotate(glm::radians(yaw), glm::radians(pitch));
}

void Engine::Player::onKeyboardInput(const Engine::WS::Event& ev)
{
	using Engine::WS::Keyboard;

	this->acceleration.x = ((1.0 * Keyboard::isButtonPressed(Keyboard::VirtualKey::W) + (-1.0 * Keyboard::isButtonPressed(Keyboard::VirtualKey::S))));
	this->acceleration.z = ((1.0 * Keyboard::isButtonPressed(Keyboard::VirtualKey::D) + (-1.0 * Keyboard::isButtonPressed(Keyboard::VirtualKey::A))));
}

void Engine::Player::process(double ticks)
{
	float speed = this->speed * ticks / TICK_COEFF;

	this->move(speed * this->acceleration);
}
