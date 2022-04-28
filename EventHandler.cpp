#include "EventHandler.h"

void Minecraft::EventHandler::onKeyboardInput(const Engine::WS::Event& ev, bool& inGame, Engine::Player& player)
{
	if (Engine::WS::Keyboard::isButtonPressed(Engine::WS::Keyboard::VirtualKey::ESC))
		inGame = !inGame;

	if (inGame)
		player.onKeyboardInput(ev);
}

void Minecraft::EventHandler::onMouseInput(const Engine::WS::Event& ev, bool& inGame, Engine::Player& player)
{
	if (inGame)
	{
		player.onMouseInput(ev);
		Engine::WS::Mouse::position(Engine::WS::Position(ev.window()->size().width / 2.0, ev.window()->size().height / 2.0), *ev.window());
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
