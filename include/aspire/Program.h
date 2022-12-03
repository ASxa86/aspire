#pragma once

#include <aspire/Shader.h>
#include <glm/glm.hpp>
#include <unordered_map>

namespace aspire
{
	class ASPIRE_EXPORT Program final
	{
	public:
		Program();
		~Program();

		Program(const Program&) = delete;
		Program& operator=(const Program&) = delete;

		Program(Program&&) noexcept = default;
		Program& operator=(Program&&) noexcept = default;

		auto getHandle() const -> unsigned int;

		template <Shader::Type T>
		Shader* addShader()
		{
			auto shader = std::make_unique<Shader>(T);
			this->shaders[T] = std::move(shader);
			return this->shaders[T].get();
		}

		auto setUniform(std::string_view x, float) -> void;
		auto setUniform(std::string_view x, glm::vec2) -> void;
		auto setUniform(std::string_view x, glm::vec3) -> void;
		auto setUniform(std::string_view x, glm::vec4) -> void;
		auto linkShaders() -> void;

		auto bind() const -> void;
		auto unbind() const -> void;

	private:
		std::unordered_map<Shader::Type, std::unique_ptr<Shader>> shaders;
		unsigned int handle{};
	};
}
