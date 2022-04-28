#pragma once
#include "Core.h"

namespace Engine
{
	namespace WS
	{
		class Event
		{
		public:
			friend class Window;

		public:
			enum class EventType
			{
				//Mouse events
				LeftMouseButtonPressed    = WM_LBUTTONDOWN,
				LeftMouseButtonReleased   = WM_LBUTTONUP,
				RightMouseButtonPressed   = WM_RBUTTONDOWN,
				RightMouseButtonReleased  = WM_RBUTTONUP,
				MiddleMouseButtonPressed  = WM_MBUTTONDOWN,
				MiddleMouseButtonReleased = WM_MBUTTONUP,
				WheelMouseScrolled        = WM_MOUSEWHEEL,
				MouseMoved                = WM_MOUSEMOVE,

				//Window events
				WindowResized             = WM_SIZE,
				WindowClosed              = WM_DESTROY,
				WindowCreated             = WM_CREATE,

				//Keyboard events
				KeyPressed            = WM_KEYDOWN,
				KeyReleased           = WM_KEYUP
			};

		private:
			EventType m_type;
			Window* m_window;

			uint64_t first_param;
			int64_t second_param;

		public:
			inline EventType type() const { return this->m_type; }
			inline char symbol() const { return (char)this->first_param; }
			inline uint32_t key() const { return (uint32_t)this->first_param; }
			inline uint8_t wheel() const { return (uint8_t)this->first_param; }
			inline Size window_size() const { return { LOWORD(this->second_param), HIWORD(this->second_param) }; }
			inline Window* window() const { return this->m_window; }
		};
	}
}