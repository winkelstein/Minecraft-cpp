#pragma once
#include "Core.h"

namespace Engine
{
	namespace WS
	{
		class Keyboard
		{
		public:
			enum class VirtualKey
			{
				Backspace = 0x08,
				Tab = 0x09,
				Enter = 0x0D,
				Shift = 0x10,
				Ctrl = 0x11,
				Alt, Pause, CapsLock,
				ESC = 0x1b,
				Space = 0x20,
				PageUp, PageDown,
				End, Home, Left,
				Up, Right, Down,
				Print = 0x2A,
				PrintScreen = 0x2C,
				Insert, Delete, Help,
				N0, N1, N2, N3, N4, N5, N6,
				N7, N8, N9,
				A = 0x41, B, C, D, E, F, G, H,
				I, J, K, L, M, N, O, P, Q, R, S, T, U,
				V, W, X, Y, Z,
				LeftWindows = 0x5B,
				RightWindow = 0x5C,
				Numpad0 = 0x60,
				Numpad1, Numpad2,
				Numpad3, Numpad4,
				Numpad5, Numpad6,
				Numpad7, Numpad8,
				Numpad9,
				F1 = 0x70,
				F2, F3, F4,
				F5, F6, F7,
				F8, F9, F10,
				F11, F12, F13,
				F14, F15, F16,
				F17, F18, F19,
				F20, F21, F22,
				F23, F24,
				NumLock = 0x90,
				LeftShift = 0xA0,
				RightShift = 0xA1,
				LeftCtrl = 0xA2,
				RightCtrl = 0xA3
			};

		public:
			static bool isButtonPressed(const VirtualKey key);
			static bool isButtonReleased(const VirtualKey key);
		};
	}
}