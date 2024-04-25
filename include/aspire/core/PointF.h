#pragma once

#include <aspire/core/export.hxx>

namespace aspire::core
{
	class ASPIRE_CORE_EXPORT PointF
	{
	public:
		PointF() = default;
		PointF(float x, float y);

		auto setX(float x) -> void;
		auto getX() const -> float;

		auto setY(float x) -> void;
		auto getY() const -> float;

	private:
		float x{};
		float y{};
	};
}