#pragma once
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

#include <glm/glm.hpp>

#include "GLObject.h"

namespace Engine
{
	namespace gltk
	{
		class Shader : public glObject
		{
		private:
			struct Uniform
			{
				std::string name;
				GLenum type;
				GLint location;
			};

		public:
			enum class ShaderType
			{
				vertex = GL_VERTEX_SHADER,
				fragment = GL_FRAGMENT_SHADER,
				geometry = GL_GEOMETRY_SHADER,
				tess_control = GL_TESS_CONTROL_SHADER,
				tess_evaluation = GL_TESS_EVALUATION_SHADER,
				compute = GL_COMPUTE_SHADER
			};

		private:
			GLuint shaders[6];

			std::vector<Uniform> uniforms;

		private:
			static std::string getSourceFromFile(std::filesystem::path pathToFile);
			static GLuint compileShader(std::string src, ShaderType type);

			void getUniforms();
			Uniform findUniform(std::string name);
		public:
			Shader();
			~Shader();

		public:
			void add(ShaderType type, std::filesystem::path pathToFile);
			void link();

		public:
			//UNSAFE! For better optimization bind function does not check link status
			void bind() const override;
			void unbind() const override;

		public:
			template<typename _Ty> void uniform(std::string name, _Ty data);
		};
	}
}

template<>
inline void Engine::gltk::Shader::uniform<int>(std::string name, int data)
{
	Uniform u = this->findUniform(name);
	if (u.type == GL_INT)
		glUniform1i(u.location, data);
}

template<>
inline void Engine::gltk::Shader::uniform<float>(std::string name, float data)
{
	Uniform u = this->findUniform(name);
	if (u.type == GL_FLOAT)
		glUniform1f(u.location, data);
}

template<>
inline void Engine::gltk::Shader::uniform<glm::vec3>(std::string name, glm::vec3 data)
{
	Uniform u = this->findUniform(name);
	if (u.type == GL_FLOAT_VEC3)
		glUniform3fv(u.location, 1, &data[0]);
}

template<>
inline void Engine::gltk::Shader::uniform<glm::vec4>(std::string name, glm::vec4 data)
{
	Uniform u = this->findUniform(name);
	if (u.type == GL_FLOAT_VEC4)
		glUniform4fv(u.location, 1, &data[0]);
}

template<>
inline void Engine::gltk::Shader::uniform<glm::mat4>(std::string name, glm::mat4 data)
{
	Uniform u = this->findUniform(name);
	if (u.type == GL_FLOAT_MAT4)
		glUniformMatrix4fv(u.location, 1, GL_FALSE, &data[0][0]);
}