#pragma once
#include "Engine/WS/Window.h"
#include "Engine/Screen.h"
#include "EventHandler.h"

#ifdef _DEBUG
#include "Engine/consolelogger.h"
#else
#include "Engine/winlogger.h"
#endif

namespace Minecraft
{
	class Application
	{
	private:
		Engine::WS::Window* window;
		Engine::Screen* screen;
		Engine::logger logger;

		bool inGame;

	public:
		Application();
		~Application();

	public:
		void run();

	private:
		static void _debugfunc(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* classptr);

	private:
		void window_init(std::string window_name, uint64_t width, uint64_t height);
		void onAnyEvent(const Engine::WS::Event& ev);
	};
}