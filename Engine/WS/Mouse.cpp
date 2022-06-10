#include "Mouse.h"

bool Engine::WS::Mouse::isButtonPressed(const MouseButton button)
{
	return GetAsyncKeyState((int)button) & 0x8000;
}

Engine::WS::Position Engine::WS::Mouse::position()
{
	POINT cursor;
	GetCursorPos(&cursor);
	Engine::WS::Position position(cursor.x, cursor.y);
	return position;
}

Engine::WS::Position Engine::WS::Mouse::position(const Window& relativeTo)
{
	POINT cursor;
	GetCursorPos(&cursor);

	ScreenToClient(relativeTo._getNativeHandler(), &cursor);
	Engine::WS::Position position(cursor.x, cursor.y);
	return position;
}

void Engine::WS::Mouse::position(const Position pos)
{
	SetCursorPos(pos.x, pos.y);
}

void Engine::WS::Mouse::position(const Position pos, const Window& relativeTo)
{
	POINT screen = { pos.x, pos.y };

	ClientToScreen(relativeTo._getNativeHandler(), &screen);
	SetCursorPos(screen.x, screen.y);
}

void Engine::WS::Mouse::visibility(bool state)
{
	ShowCursor(state ? TRUE : FALSE);
}

void Engine::WS::Mouse::clip(const Window& window, bool state)
{
	if (state)
	{
		RECT r;
		GetWindowRect(window._getNativeHandler(), &r);
		ClipCursor(&r);
	}
	else
		ClipCursor(NULL);
}
