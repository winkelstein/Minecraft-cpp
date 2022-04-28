#include "Texture.h"

Engine::gltk::Texture::Texture(const unsigned char* data, uint64_t width, uint64_t height, uint8_t nrChannels)
{
	glGenTextures(1, &this->handler);
	this->bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Engine::gltk::Texture::~Texture()
{
	glDeleteTextures(1, &this->handler);
}

void Engine::gltk::Texture::active(uint8_t base) const
{
	glActiveTexture(GL_TEXTURE0 + base);
}

void Engine::gltk::Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->handler);
}

void Engine::gltk::Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, NULL);
}

Engine::gltk::TextureColorBuffer::TextureColorBuffer(uint64_t width, uint64_t height) : Texture(NULL, width, height, 0)
{
	this->resize(width, height);
}

void Engine::gltk::TextureColorBuffer::resize(uint64_t width, uint64_t height)
{
	this->bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
}
