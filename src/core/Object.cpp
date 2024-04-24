#include <aspire/core/Object.h>

using aspire::core::Object;

auto Object::setName(std::string_view x) -> void
{
	this->name = x;
}

auto Object::getName() const -> std::string_view
{
	return this->name;
}
