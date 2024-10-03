#pragma once

#include <aspire/scene/Node.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace aspire::scene
{
	class ASPIRE_SCENE_EXPORT NodeGeometry : public Node
	{
	public:
		struct Vertex
		{
			glm::vec2 position{};
			glm::vec4 color{};
			glm::vec2 texCoord{};
		};

		auto setVertices(std::vector<Vertex> x) -> void;
		[[nodiscard]] auto getVertices() const noexcept -> const std::vector<Vertex>&;

	private:
		std::vector<Vertex> vertices;
	};
}
