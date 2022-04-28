#pragma once
#include <cstdint>

#include "GLObject.h"
#include "Texture.h"

namespace Engine
{
	namespace gltk
	{
		class RenderBuffer : public glObject
		{
			friend class Framebuffer;
		public:
			RenderBuffer(uint64_t width, uint64_t height);
			~RenderBuffer();

		public:
			void resize(uint64_t width, uint64_t height);

		public:
			void bind() const override;
			void unbind() const override;
		};

		class Framebuffer : public glObject
		{
		private:
			TextureColorBuffer tcb;
			RenderBuffer rbo;

		public:
			Framebuffer(uint64_t width, uint64_t height);
			~Framebuffer();

		public:
			void resize(uint64_t width, uint64_t height);
			inline Texture texture() const
			{
				return this->tcb;
			}

		public:
			void bind() const override;
			void unbind() const override;
		};
	}
}