#include <aspire/core/Event.h>
#include <aspire/core/PimplImpl.h>

using aspire::core::Event;

struct Event::Impl
{
	Impl(Type x) : type{x}
	{
	}

	Type type{Type::Unknown};
};

Event::Event(Type x) : pimpl{x}
{
}

Event::~Event() = default;

auto Event::type() const -> Type
{
	return this->pimpl->type;
}
