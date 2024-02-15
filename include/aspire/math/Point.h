#pragma once

#include <array>
#include <aspire/math/export.hxx>

namespace aspire
{
	class ASPIRE_MATH_EXPORT Point
	{
	public:
		Point() = default;

		auto setX(double x) noexcept -> void;
		auto getX() const noexcept -> double;

		auto setY(double x) noexcept -> void;
		auto getY() const noexcept -> double;

	private:
		std::array<double, 2> point{};
	};
}
