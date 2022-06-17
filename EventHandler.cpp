#include "EventHandler.h"

void Minecraft::EventHandler::onKeyboardInput(const Engine::WS::Event& ev, bool& inGame, Engine::Player& player, Engine::WS::Window& window)
{
	using namespace Engine::WS;

	if (Engine::WS::Keyboard::isButtonPressed(Keyboard::VirtualKey::ESC))
	{
		inGame = !inGame;
		Engine::WS::Mouse::clip(window, inGame);
	}

	if (inGame)
		player.onKeyboardInput(ev);
}

void Minecraft::EventHandler::onMouseInput(const Engine::WS::Event& ev, bool& inGame, Engine::Player& player)
{
	using namespace Engine::WS;

	if (inGame)
	{
		player.onMouseInput(ev);
		Mouse::position(Position(ev.window()->size().width / 2.0, ev.window()->size().height / 2.0), *ev.window());
	}
}

void Minecraft::EventHandler::onClose(const Engine::WS::Event& ev, Engine::WS::Window& window)
{
	window.close();
}

void Minecraft::EventHandler::onResize(const Engine::WS::Event& ev, Engine::Screen& scr)
{
	scr.resize(Engine::WS::Size(ev.window_size().width, ev.window_size().height));
}
