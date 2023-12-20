#include <aspire/core/Event.h>

using aspire::Event;

Event::Event(Type x) : type{x}
{
}

auto Event::getType() const -> Type
{
	return this->type;
}
