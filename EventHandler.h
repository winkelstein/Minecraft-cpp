#pragma once
#include "Engine/WS/Event.h"
#include "Engine/WS/Window.h"
#include "Engine/Screen.h"
#include "Engine/Player.h"

namespace Minecraft
{
	class EventHandler
	{
	public:
		static void onKeyboardInput(const Engine::WS::Event& ev, bool& inGame, Engine::Player& player);
		static void onMouseInput(const Engine::WS::Event& ev, bool& inGame, Engine::Player& player);
		static void onClose(const Engine::WS::Event& ev, Engine::WS::Window& window);
		static void onResize(const Engine::WS::Event& ev, Engine::Screen& scr);
	};
}