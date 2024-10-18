#pragma once

#include <aspire/graphics/export.hxx>

namespace aspire
{
	struct ASPIRE_GRAPHICS_EXPORT Color
	{
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Black;
		static const Color White;

		float red{};
		float green{};
		float blue{};
		float alpha{1.0F};
	};

	inline constexpr Color Color::Red{.red = 1.0F};
	inline constexpr Color Color::Green{.green = 1.0F};
	inline constexpr Color Color::Blue{.blue = 1.0F};
	inline constexpr Color Color::White{.red = 1.0F, .green = 1.0F, .blue = 1.0F};
	inline constexpr Color Color::Black{};
}
