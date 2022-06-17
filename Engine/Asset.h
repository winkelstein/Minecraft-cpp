#pragma once
#include <unordered_map>

#include "Model.h"
#include "GLTK/Texture.h"
#include "GLTK/Shader.h"

namespace Engine
{
	class Asset
	{
	private:
		std::unordered_map<std::string, std::shared_ptr<Mesh>> meshes;
		std::unordered_map<std::string, std::shared_ptr<gltk::Texture>> textures;
		std::unordered_map<std::string, std::shared_ptr<gltk::Shader>> shaders;

	public:
		template <class _Ty> void store(std::string name, _Ty object);
		template <class _Ty> const _Ty get(std::string name);
	};
}

template<> inline void Engine::Asset::store(std::string name, std::shared_ptr<Mesh> object)
{
	this->meshes[name] = object;
}

template<> inline void Engine::Asset::store(std::string name, std::shared_ptr<Engine::gltk::Texture> object)
{
	this->textures[name] = object;
}

template<> inline void Engine::Asset::store(std::string name, std::shared_ptr<Engine::gltk::Shader> object)
{
	this->shaders[name] = object;
}

template<> inline const std::shared_ptr<Engine::Mesh> Engine::Asset::get(std::string name)
{
	if (this->meshes.find(name) != this->meshes.end())
		return this->meshes[name];
	else
		throw std::exception("Model not found");
}

template<> inline const std::shared_ptr<Engine::gltk::Texture> Engine::Asset::get(std::string name)
{
	if (this->textures.find(name) != this->textures.end())
		return this->textures[name];
	else
		throw std::exception("Texture not found");
}

template<> inline const std::shared_ptr<Engine::gltk::Shader> Engine::Asset::get(std::string name)
{
	if (this->shaders.find(name) != this->shaders.end())
		return this->shaders[name];
	else
		throw std::exception("Shader not found");
}