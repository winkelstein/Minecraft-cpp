#pragma once
#pragma warning(disable: 4996)

#include <string>
#include <queue>
#include <mutex>
#include <ctime>

namespace Engine
{
	class Logger
	{
	public:
		enum class severity
		{
			high = 3, medium = 2, low = 1, notification = 0
		};

		struct message
		{
			std::string header;
			std::string body;
			severity sev;

			message(std::string header, std::string body, severity sev = severity::notification)
			{
				this->header = header;
				this->body = body;
				this->sev = sev;
			}
		};

	protected:
		std::queue<message> qMessages;
		std::recursive_mutex mtx;

		std::atomic<bool> isWorking;

		inline std::tm currentTime()
		{
			std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			std::tm* now = std::localtime(&time);
			return *now;
		}

	public:
		friend Logger& operator<< (Logger& logger, const message& msg)
		{
			std::lock_guard<std::recursive_mutex> lock(logger.mtx);
			logger.qMessages.push(msg);

			return logger;
		}

	public:
		void flush();

	protected:
		virtual void out(const message& msg) = 0;
	};
}