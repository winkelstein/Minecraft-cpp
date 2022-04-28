#pragma once
#include <queue>
#include <string>
#include <exception>

#include "Core.h"
#include "Event.h"
#include "../GLTK/glContext.h"

#include "../../resource.h"

/* I prefer to use my own Window System (WS) created using Win32API */
namespace Engine
{
	namespace WS
	{
		class Window : public gltk::_glContext::glContext
		{
		private:
			HWND m_handler;
			bool isWorking;

			std::queue<Event> events;
		private:
			void registerWindowClass(std::string class_name, HINSTANCE hInstance);
			HWND createNativeWindow(std::string name, std::string class_name, HINSTANCE hInstance, const Size size, const Position pos);

			static LRESULT CALLBACK _winproc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		public:
			Window(const Window&) = delete;
			Window& operator=(const Window&) = delete;

		public:
			Window(std::string name, const Size size, const Position position);
			~Window();

		public:
			void close();
			void setFullscreenMode(bool state);

			Size size() const;
			bool pollEvent(Event& ev);

		public:
			inline bool isOpen() const { return this->isWorking; }
			inline HWND _getNativeHandler() const { return this->m_handler; }
		};
	}
}