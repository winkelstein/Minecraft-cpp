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
		std::unordered_map<std::string, Model*> models;
		std::unordered_map<std::string, gltk::Texture*> textures;
		std::unordered_map<std::string, gltk::Shader*> shaders;

	public:
		template <class _Ty> void store(std::string name, _Ty& object);
		template <class _Ty> const _Ty& get(std::string name);

	public:
		~Asset()
		{
			for (auto& el : this->models)
				delete el.second;

			for (auto& el : this->textures)
				delete el.second;

			for (auto& el : this->shaders)
				delete el.second;
		}
	};
}

template<> inline void Engine::Asset::store(std::string name, Engine::Model& object)
{
	this->models[name] = &object;
}

template<> inline void Engine::Asset::store(std::string name, Engine::gltk::Texture& object)
{
	this->textures[name] = &object;
}

template<> inline void Engine::Asset::store(std::string name, Engine::gltk::Shader& object)
{
	this->shaders[name] = &object;
}

template<> inline const Engine::Model& Engine::Asset::get(std::string name)
{
	if (this->models.find(name) != this->models.end())
		return *this->models[name];
	else
		throw std::exception("Model not found");
}

template<> inline const Engine::gltk::Texture& Engine::Asset::get(std::string name)
{
	if (this->textures.find(name) != this->textures.end())
		return *this->textures[name];
	else
		throw std::exception("Texture not found");
}

template<> inline const Engine::gltk::Shader& Engine::Asset::get(std::string name)
{
	if (this->shaders.find(name) != this->shaders.end())
		return *this->shaders[name];
	else
		throw std::exception("Shader not found");
}