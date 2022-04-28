#pragma once
#include <fstream>
#include <Windows.h>
#include "Logger.h"

namespace Engine
{
	class logger : public Logger
	{
	private:
		void out(const Logger::message& msg) override
		{
			std::lock_guard<std::recursive_mutex> lock(this->mtx);
			static std::ofstream outputfile("debug.log");

			if (msg.sev == severity::high)
				MessageBoxA(nullptr, msg.body.c_str(), msg.header.c_str(), MB_ICONERROR);

			std::tm now = this->currentTime();
			outputfile << "[" << now.tm_hour << ":" << now.tm_min << ":" << now.tm_sec << "] " << msg.header << ": " << msg.body << std::endl;
		}
	};
}