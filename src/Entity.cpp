#include <aspire/Entity.h>

using aspire::Entity;

Entity::Entity(int x) : id{x}
{
}

auto Entity::setID(int x) noexcept -> void
{
	this->id = x;
}

auto Entity::getID() const noexcept -> int
{
	return this->id;
}

auto Entity::setRotation(double x) noexcept -> void
{
	this->rotation = x;
}

auto Entity::getRotation() const noexcept -> double
{
	return this->rotation;
}
