#include "Keyboard.h"

bool Engine::WS::Keyboard::isButtonPressed(const VirtualKey key)
{
    return GetAsyncKeyState((int)key) & 0x8000;
}

bool Engine::WS::Keyboard::isButtonReleased(const VirtualKey key)
{
    return !(GetAsyncKeyState((int)key) & 0x8000);
}
