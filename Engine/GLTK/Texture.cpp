#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Engine::gltk::Texture::Texture(std::filesystem::path path)
{
	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.string().c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		glGenTextures(1, &this->handler);
		glBindTexture(GL_TEXTURE_2D, this->handler);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		stbi_image_free(data);
	}
	else
	{
		stbi_image_free(data);
		throw std::exception("Unable to create texture");
	}
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