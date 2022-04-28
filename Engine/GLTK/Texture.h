#pragma once
#include <cstdint>
#include <exception>

#include "GLObject.h"

namespace Engine
{
	namespace gltk
	{
		class Texture : public glObject
		{
		public:
			Texture(const unsigned char* data, uint64_t width, uint64_t height, uint8_t nrChannels);
			~Texture();

		public:
			void active(uint8_t base) const;

		public:
			void bind() const override;
			void unbind() const override;
		};

		class TextureColorBuffer : public Texture
		{
			friend class Framebuffer;
		public:
			TextureColorBuffer(uint64_t width, uint64_t height);

		public:
			void resize(uint64_t width, uint64_t height);
		};
	}
}