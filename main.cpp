#include <Windows.h>
#include "Application.h"

#ifdef _DEBUG
int main(int argc, const char** argv)
{
	Minecraft::Application app;
	app.run();
}
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdLine, int nCmdShow)
{
	Minecraft::Application app;
	app.run();
}
#endif