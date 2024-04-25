#pragma once

#include <aspire/core/export.hxx>

namespace aspire::core
{
	class ASPIRE_CORE_EXPORT Point
	{
	public:
		Point() = default;
		Point(int x, int y);

		auto setX(int x) -> void;
		auto getX() const -> int;

		auto setY(int x) -> void;
		auto getY() const -> int;

	private:
		int x{};
		int y{};
	};
}