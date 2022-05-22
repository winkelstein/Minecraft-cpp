#pragma once
#include <cstdint>
#include <exception>
#include <filesystem>

#include "GLObject.h"

namespace Engine
{
	namespace gltk
	{
		class Texture : public glObject
		{
		public:
			Texture(std::filesystem::path path);

		public:
			void active(uint8_t base) const;

		public:
			void bind() const override;
			void unbind() const override;
		};
	}
}