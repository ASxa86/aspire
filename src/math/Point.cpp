#include <aspire/math/Point.h>

using aspire::Point;

auto Point::setX(double x) noexcept -> void
{
	this->point[0] = x;
}

auto Point::getX() const noexcept -> double
{
	return this->point[0];
}

auto Point::setY(double x) noexcept -> void
{
	this->point[1] = x;
}

auto Point::getY() const noexcept -> double
{
	return this->point[1];
}
