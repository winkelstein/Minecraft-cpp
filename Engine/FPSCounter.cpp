#include "FPSCounter.h"

Engine::FPSCounter::FPSCounter() : m_ticks(0.1)
{
}

void Engine::FPSCounter::start()
{
	this->time = std::chrono::high_resolution_clock::now();
}

void Engine::FPSCounter::end()
{
	auto end = std::chrono::high_resolution_clock::now();

	this->m_ticks = (end - this->time).count() / 1000000.0;
}
