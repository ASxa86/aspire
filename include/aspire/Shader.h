#pragma once

#include <angle_gl.h>
#include <aspire/export.hxx>
#include <filesystem>

namespace aspire
{
	class Shader final
	{
	public:
		enum class Type : int
		{
			Vertex = GL_VERTEX_SHADER,
			Fragment = GL_FRAGMENT_SHADER
		};

		explicit Shader(Type x);
		~Shader();

		auto loadFromFile(const std::filesystem::path& x) -> bool;
		auto loadFromMemory(std::string_view x) -> bool;

		auto getType() const -> Type;
		auto getHandle() const -> unsigned int;

	private:
		Type type{};
		unsigned int handle{};
	};
}
