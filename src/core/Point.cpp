#include <aspire/core/Point.h>

using aspire::core::Point;

Point::Point(int x, int y) : x{x}, y{y}
{
}

auto Point::setX(int x) -> void
{
	this->x = x;
}

auto Point::getX() const -> int
{
	return this->x;
}

auto Point::setY(int x) -> void
{
	this->y = x;
}

auto Point::getY() const -> int
{
	return this->y;
}
