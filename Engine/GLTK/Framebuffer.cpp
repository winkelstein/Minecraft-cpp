#include "Framebuffer.h"

Engine::gltk::RenderBuffer::RenderBuffer(uint64_t width, uint64_t height)
{
	glGenRenderbuffers(1, &this->handler);
	this->bind();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

Engine::gltk::RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &this->handler);
}

void Engine::gltk::RenderBuffer::resize(uint64_t width, uint64_t height)
{
	this->bind();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

void Engine::gltk::RenderBuffer::bind() const
{
	glBindRenderbuffer(GL_RENDERBUFFER, this->handler);
}

void Engine::gltk::RenderBuffer::unbind() const
{
	glBindRenderbuffer(GL_RENDERBUFFER, NULL);
}

Engine::gltk::Framebuffer::Framebuffer(uint64_t width, uint64_t height) : tcb(width, height), rbo(width, height)
{
	glGenFramebuffers(1, &this->handler);
	this->bind();

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->tcb.handler, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rbo.handler);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw std::exception("framebuffer is incomplete");
}

Engine::gltk::Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &this->handler);
}

void Engine::gltk::Framebuffer::resize(uint64_t width, uint64_t height)
{
	this->tcb.resize(width, height);
	this->rbo.resize(width, height);
}

void Engine::gltk::Framebuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->handler);
}

void Engine::gltk::Framebuffer::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, NULL);
}
