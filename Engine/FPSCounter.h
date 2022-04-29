#pragma once
#include <chrono>

namespace Engine
{
	class FPSCounter
	{
	private:
		double m_ticks;

		std::chrono::steady_clock::time_point time;
	public:
		FPSCounter();
		
	public:
		void start();
		void end();

	public:
		inline double ticks() const { return this->m_ticks; }
	};
}