#pragma once

#include <aspire/scene/NodeGeometry.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace aspire::scene
{
	class ASPIRE_SCENE_EXPORT NodeRectangle : public NodeGeometry
	{
	public:
		auto setColor(glm::vec4 x) noexcept -> void;
		[[nodiscard]] auto getColor() const noexcept -> glm::vec4;

		auto setPosition(glm::vec2 x) noexcept -> void;
		[[nodiscard]] auto getPosition() const noexcept -> glm::vec2;

		auto setSize(glm::vec2 x) noexcept -> void;
		[[nodiscard]] auto getSize() const noexcept -> glm::vec2;

	private:
		glm::vec4 color{};
		glm::vec2 position{};
		glm::vec2 size{};
	};
}
