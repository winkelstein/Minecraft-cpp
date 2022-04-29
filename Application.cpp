#include "Application.h"

Minecraft::Application::Application()
{
	try
	{
		this->window_init("Minecraft-cpp", 1000, 600);
	}
	catch (std::exception& e)
	{
		this->logger << Engine::Logger::message("WinAPI", e.what(), Engine::Logger::severity::high);
	}
	this->logger << Engine::Logger::message("WinAPI", "window has been created");

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(this->_debugfunc, &this->logger);

	this->player = new Engine::Player("Steve");

	this->inGame = true;
}

Minecraft::Application::~Application()
{
	delete this->player;
	delete this->screen;
	delete this->window;
}

void Minecraft::Application::run()
{
	Engine::FPSCounter counter;
	while (this->window->isOpen())
	{
		counter.start();
		{
			//Events
			Engine::WS::Event event;
			while (this->window->pollEvent(event))
				this->onAnyEvent(event);

			//Logging
			this->logger.flush();


			//Player process
			this->player->process(counter.ticks());
			this->screen->onUpdateCamera(this->player->camera());

			//Draw things


			this->screen->render();
			this->window->swapBuffers();
			this->window->clearColor(128.0 / 255.0, 166.0 / 255.0, 1, 1.0);
			this->window->clear();
		}
		counter.end();
	}
}

void Minecraft::Application::_debugfunc(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* classptr)
{
	Engine::Logger* logger = (Engine::Logger*)classptr;

	Engine::Logger::severity sev;
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		sev = Engine::Logger::severity::high;
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		sev = Engine::Logger::severity::medium;
		break;
	case GL_DEBUG_SEVERITY_LOW:
		sev = Engine::Logger::severity::low;
		break;
	default:
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		sev = Engine::Logger::severity::notification;
		break;
	}

	*logger << Engine::Logger::message("OpenGL", message, sev);
}

void Minecraft::Application::window_init(std::string window_name, uint64_t width, uint64_t height)
{
	this->window = new Engine::WS::Window(window_name, Engine::WS::Size(width, height), Engine::WS::Position(0, 0));
	this->screen = new Engine::Screen(Engine::WS::Size(width, height));
}

void Minecraft::Application::onAnyEvent(const Engine::WS::Event& ev)
{
	using Engine::WS::Event;

	switch (ev.type())
	{
	case Event::EventType::WindowClosed:
		EventHandler::onClose(ev, *this->window);
		break;
	case Event::EventType::WindowResized:
		EventHandler::onResize(ev, *this->screen);
		break;
	case Event::EventType::KeyPressed:
	case Event::EventType::KeyReleased:
		EventHandler::onKeyboardInput(ev, this->inGame, *this->player, *this->window);
		break;
	case Event::EventType::MouseMoved:
	case Event::EventType::LeftMouseButtonPressed:
	case Event::EventType::LeftMouseButtonReleased:
	case Event::EventType::RightMouseButtonPressed:
	case Event::EventType::RightMouseButtonReleased:
	case Event::EventType::MiddleMouseButtonPressed:
	case Event::EventType::MiddleMouseButtonReleased:
	case Event::EventType::WheelMouseScrolled:
		EventHandler::onMouseInput(ev, this->inGame, *this->player);
		break;
	}
}
