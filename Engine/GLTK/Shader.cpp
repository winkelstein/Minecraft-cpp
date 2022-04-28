#include "Shader.h"

std::string Engine::gltk::Shader::getSourceFromFile(std::filesystem::path pathToFile)
{
	std::ifstream file(pathToFile);
	if (!file.is_open())
		throw std::runtime_error("unable to open shader file");

	std::string src, buffer;
	while (std::getline(file, buffer))
		src += buffer + '\n';

	return src;
}

GLuint Engine::gltk::Shader::compileShader(std::string src, ShaderType type)
{
	GLuint shader = glCreateShader((GLenum)type);
	const char* str = src.c_str();
	glShaderSource(shader, 1, &str, nullptr);

	glCompileShader(shader);

	int status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::string infoLog;
		infoLog.resize(512);
		glGetShaderInfoLog(shader, 512, nullptr, &infoLog[0]);
		throw std::exception(infoLog.c_str());
	}
	else return shader;
}

void Engine::gltk::Shader::getUniforms()
{
	int numUniforms = 0;
	glGetProgramInterfaceiv(this->handler, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);

	this->uniforms.resize(numUniforms);

	GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX };

	for (size_t i = 0; i < numUniforms; i++)
	{
		GLint results[4];
		glGetProgramResourceiv(this->handler, GL_UNIFORM, i, 4, properties, 4, nullptr, results);

		if (results[3] != -1) continue;

		GLint nameBufSize = results[0];
		std::string name;
		name.resize(nameBufSize);

		glGetProgramResourceName(this->handler, GL_UNIFORM, i, nameBufSize, nullptr, &name[0]);

		this->uniforms[i].name = name.substr(0, name.size() - 1);
		this->uniforms[i].type = results[1];
		this->uniforms[i].location = results[2];
	}
}

Engine::gltk::Shader::Uniform Engine::gltk::Shader::findUniform(std::string name)
{
	for (size_t i = 0; i < this->uniforms.size(); i++)
		if (name == this->uniforms[i].name)
			return this->uniforms[i];

	throw std::exception("specified uniform was not found");
}

Engine::gltk::Shader::Shader()
{
	memset(this->shaders, 0, sizeof(this->shaders));
}

Engine::gltk::Shader::~Shader()
{
	glDeleteProgram(this->handler);
}

void Engine::gltk::Shader::add(ShaderType type, std::filesystem::path pathToFile)
{
	uint8_t i = 0;
	while (this->shaders[i] != 0)
		i++;

	if (i > 6) throw std::exception("too much shaders");
	else this->shaders[i] = Shader::compileShader(Shader::getSourceFromFile(pathToFile), type);
}

void Engine::gltk::Shader::link()
{
	this->handler = glCreateProgram();
	for (uint8_t i = 0; i < this->shaders[i] != 0; i++)
		glAttachShader(this->handler, this->shaders[i]);

	glLinkProgram(this->handler);

	int status;
	glGetProgramiv(this->handler, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::string infoLog;
		infoLog.resize(512);
		glGetProgramInfoLog(this->handler, 512, nullptr, &infoLog[0]);
		throw std::exception(infoLog.c_str());
	}

	for (uint8_t i = 0; i < this->shaders[i] > 0; i++)
		glDeleteShader(this->shaders[i]);

	this->getUniforms();
}

void Engine::gltk::Shader::bind() const
{
	glUseProgram(this->handler);
}

void Engine::gltk::Shader::unbind() const
{
	glUseProgram(0);
}
