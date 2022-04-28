#include "Logger.h"

void Engine::Logger::flush()
{
	while (!this->qMessages.empty())
	{
		this->out(this->qMessages.front());
		this->qMessages.pop();
	}
}