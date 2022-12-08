#include <aspire/Program.h>

using aspire::Program;

Program::Program()
{
	this->handle = glCreateProgram();
}

Program::~Program()
{
	glDeleteProgram(this->handle);
}

auto Program::getHandle() const -> unsigned int
{
	return this->handle;
}

auto Program::setUniform(std::string_view x, float v) -> void
{
	const auto location = glGetUniformLocation(this->handle, x.data());
	glUniform1f(location, v);
}

auto Program::setUniform(std::string_view x, glm::vec2 v) -> void
{
	const auto location = glGetUniformLocation(this->handle, x.data());
	glUniform2f(location, v.x, v.y);
}

auto Program::setUniform(std::string_view x, glm::vec3 v) -> void
{
	const auto location = glGetUniformLocation(this->handle, x.data());
	glUniform3f(location, v.x, v.y, v.z);
}

auto Program::setUniform(std::string_view x, glm::vec4 v) -> void
{
	const auto location = glGetUniformLocation(this->handle, x.data());
	glUniform4f(location, v.r, v.g, v.b, v.a);
}

auto Program::linkShaders() -> void
{
	for(const auto& [type, shader] : this->shaders)
	{
		glAttachShader(this->handle, shader->getHandle());
	}

	glLinkProgram(this->handle);
}

auto Program::use() const -> void
{
	glUseProgram(this->handle);
}

auto Program::release() const -> void
{
	glUseProgram(0);
}
