#pragma once
#include <iostream>
#include "Logger.h"

namespace Engine
{
	class logger : public Logger
	{
	private:
		void Engine::Logger::out(const message& msg)
		{
			std::lock_guard<std::recursive_mutex> lock(this->mtx);
			std::tm now = this->currentTime();

			if (msg.sev != severity::notification)
				std::cerr << "[" << now.tm_hour << ":" << now.tm_min << ":" << now.tm_sec << "] " << msg.header << ": " << msg.body << std::endl;
			else
				std::cout << "[" << now.tm_hour << ":" << now.tm_min << ":" << now.tm_sec << "] " << msg.header << ": " << msg.body << std::endl;
		}
	};
}