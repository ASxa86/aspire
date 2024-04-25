#include <aspire/core/PointF.h>

using aspire::core::PointF;

PointF::PointF(float x, float y) : x{x}, y{y}
{
}

auto PointF::setX(float x) -> void
{
	this->x = x;
}

auto PointF::getX() const -> float
{
	return this->x;
}

auto PointF::setY(float x) -> void
{
	this->y = x;
}

auto PointF::getY() const -> float
{
	return this->y;
}
