#include "Window.h"

void Engine::WS::Window::registerWindowClass(std::string class_name, HINSTANCE hInstance)
{
	WNDCLASSEXA wcex;
	memset(&wcex, 0, sizeof(wcex));

	wcex.cbSize = sizeof(wcex);
	wcex.lpszClassName = class_name.c_str();
	wcex.lpfnWndProc = Window::_winproc;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursorW(wcex.hInstance, IDC_ARROW);
	wcex.hIcon = LoadIconW(wcex.hInstance, MAKEINTRESOURCEW(IDI_ICON1));
	wcex.hIconSm = LoadIconW(wcex.hInstance, MAKEINTRESOURCEW(IDI_ICON1));
	wcex.hbrBackground = NULL;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.lpszMenuName = nullptr;
	wcex.style = CS_OWNDC;

	if (!RegisterClassExA(&wcex))
		throw std::exception("Unable to register window class");
}

HWND Engine::WS::Window::createNativeWindow(std::string name, std::string class_name, HINSTANCE hInstance, const Size size, const Position pos)
{
	HWND m_handler = CreateWindowExA(NULL, class_name.c_str(), name.c_str(), WS_CAPTION | WS_SYSMENU | WS_SIZEBOX | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, pos.x, pos.y, size.width, size.height, nullptr, nullptr, hInstance, this);

	if (!m_handler)
		throw std::exception("Unable to create a window");

	UpdateWindow(m_handler);
	ShowWindow(m_handler, SW_SHOWDEFAULT);

	return m_handler;
}

LRESULT Engine::WS::Window::_winproc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* window = nullptr;

	if (msg == WM_NCCREATE)
	{
		window = static_cast<Window*>(reinterpret_cast<LPCREATESTRUCTA>(lParam)->lpCreateParams);

		SetLastError(0);
		if (!SetWindowLongPtrA(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window)))
			if (GetLastError())
				throw std::exception("Unable to set window long pointer");
	}
	else
	{
		window = reinterpret_cast<Window*>(GetWindowLongPtrA(hWnd, GWLP_USERDATA));
	}

	if (window)
	{
		//Now we need to push new event to the event queue
		window->m_handler = hWnd;
		Event event;
		event.m_type = (Event::EventType)msg;
		event.first_param = wParam;
		event.second_param = lParam;
		event.m_window = window;

		window->events.push(event);
	}

	return DefWindowProcA(hWnd, msg, wParam, lParam);
}

Engine::WS::Window::Window(std::string name, const Size size, const Position position)
{
	HINSTANCE hInstance = GetModuleHandleA(nullptr);
	this->isWorking = true;

	std::string class_name = name + "WCLASS";

	try
	{
		this->registerWindowClass(class_name, hInstance);
		this->m_handler = this->createNativeWindow(name, class_name, hInstance, size, position);
		this->createContext(this->m_handler);
	}
	catch (std::exception& e)
	{
		throw e;
	}
}

Engine::WS::Window::~Window()
{
	DestroyWindow(this->m_handler);
}

void Engine::WS::Window::close()
{
	this->isWorking = false;
	this->~Window();
}

void Engine::WS::Window::setFullscreenMode(bool state)
{
	ShowWindow(this->m_handler, state);
}

Engine::WS::Size Engine::WS::Window::size() const
{
	RECT rect;
	GetWindowRect(this->m_handler, &rect);
	uint64_t width = rect.right - rect.left;
	uint64_t height = rect.bottom - rect.top;
	return {width, height};
}

bool Engine::WS::Window::pollEvent(Event& ev)
{
	//Check for new events
	if (this->events.empty())
	{
		MSG msg;
		while (PeekMessageA(&msg, this->m_handler, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}

	//...or take event from event queue
	if (!this->events.empty())
	{
		ev = this->events.front();
		this->events.pop();

		return true;
	}

	return false;
}
