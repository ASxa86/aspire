#pragma once

#include <aspire/scene/Node.h>
#include <glm/mat4x4.hpp>

namespace aspire::scene
{
	class ASPIRE_SCENE_EXPORT NodeTransform : public Node
	{
	public:
		auto setMatrix(glm::mat4 x) noexcept -> void;
		[[nodiscard]] auto getMatrix() const noexcept -> glm::mat4;

	private:
		glm::mat4 matrix;
	};
}
