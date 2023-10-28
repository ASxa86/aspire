#include <aspire/Entity.h>

using aspire::Entity;

auto Entity::setRotation(double x) noexcept -> void
{
	this->rotation = x;
}

auto Entity::getRotation() const noexcept -> double
{
	return this->rotation;
}
