#pragma once

#include <aspire/graphics/Color.h>

namespace aspire
{
	struct Vec2
	{
		float x{};
		float y{};
	};

	struct Vertex
	{
		Vec2 position{};
		Color color{};
		Vec2 texCoords{1.0F, 1.0F};
	};
}
