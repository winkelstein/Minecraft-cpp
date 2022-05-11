#pragma once
#include "Engine/WS/Window.h"
#include "Engine/Screen.h"
#include "EventHandler.h"
#include "Engine/FPSCounter.h"
#include "Engine/GLTK/Shader.h"
#include "Engine/Model.h"
#include "Engine/Asset.h"
#include "Engine/Block/BlockImporter.h"
#include "Engine/World/World.h"

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
		Engine::Player* player;
		Engine::Asset assets;
		Engine::BlockImporter* block_importer;
		Engine::World world;

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
		void assets_init();
		void world_generate();
		void onAnyEvent(const Engine::WS::Event& ev);
	};
}