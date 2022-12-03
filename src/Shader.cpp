#include <aspire/Shader.h>
#include <fstream>

using aspire::Shader;

Shader::Shader(Type x) : type{x}
{
	this->handle = glCreateShader(static_cast<GLenum>(this->type));
}

Shader::~Shader()
{
	glDeleteShader(this->handle);
}

auto Shader::loadFromFile(const std::filesystem::path& x) -> bool
{
	std::string buffer;

	std::ifstream in{x};

	if(in.is_open() == true)
	{
		in.seekg(0, std::ios::end);
		buffer.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(buffer.data(), buffer.size());
	}

	return this->loadFromMemory(buffer);
}

auto Shader::loadFromMemory(std::string_view x) -> bool
{
	const auto source = x.data();
	const auto length = static_cast<GLint>(x.size());
	glShaderSource(this->handle, 1, &source, &length);
	glCompileShader(this->handle);

	int success;
	glGetShaderiv(this->handle, GL_COMPILE_STATUS, &success);
	return success == 0;
}

auto Shader::getType() const -> Type
{
	return this->type;
}

auto Shader::getHandle() const -> unsigned int
{
	return this->handle;
}
