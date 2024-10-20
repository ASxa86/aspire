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

		std::uint8_t red{};
		std::uint8_t green{};
		std::uint8_t blue{};
		std::uint8_t alpha{std::numeric_limits<std::uint8_t>::max()};
	};

	inline constexpr Color Color::Red{.red = std::numeric_limits<std::uint8_t>::max()};
	inline constexpr Color Color::Green{.green = std::numeric_limits<std::uint8_t>::max()};
	inline constexpr Color Color::Blue{.blue = std::numeric_limits<std::uint8_t>::max()};
	inline constexpr Color Color::White{.red = std::numeric_limits<std::uint8_t>::max(),
										.green = std::numeric_limits<std::uint8_t>::max(),
										.blue = std::numeric_limits<std::uint8_t>::max()};
	inline constexpr Color Color::Black{};
}
