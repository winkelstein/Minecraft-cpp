#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	class Camera
	{
	protected:
		glm::vec3 m_position;
		glm::vec3 m_front;
		glm::mat4 m_view;

	protected:
		void updateView();

	public:
		Camera(glm::vec3 position = glm::vec3(0.0, 0.0, 0.0));

	public:
		void rotate(float yaw, float pitch);

		void position(glm::vec3 position);
		virtual void move(glm::vec3 position);

	public:
		inline glm::mat4 view() const { return this->m_view; }
		inline glm::vec3 position() const { return this->m_position; }
		inline glm::vec3 front() const { return this->m_front; }
	};
}