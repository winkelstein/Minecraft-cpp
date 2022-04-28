#pragma once
#include "Core.h"
#include "Window.h"

namespace Engine
{
	namespace WS
	{
		class Mouse
		{
		public:
			enum class MouseButton
			{
				Left   = 0x01,
				Right  = 0x02,
				Middle = 0x04,
				X1     = 0x05,
				X2     = 0x06
			};

		public:
			static bool isButtonPressed(const MouseButton button);
			static Position position();
			static Position position(const Window& relativeTo);
			static void position(const Position pos);
			static void position(const Position pos, const Window& relativeTo);

			static void visibility(bool state);
			static void clip(const Window& window, bool state);
		};
	}
}