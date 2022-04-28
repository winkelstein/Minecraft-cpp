#pragma once
#include <cstdint>
#include <Windows.h>

namespace Engine
{
	namespace WS
	{
		struct Size
		{
			uint64_t width, height;
		};

		struct Position
		{
			uint64_t x, y;
		};
	}
}