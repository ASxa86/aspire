#include <aspire/core/Signal.h>

using aspire::impl::SignalBase;

SignalBase::~SignalBase()
{
	for(auto* cx : this->slots)
	{
		cx->disconnect();
	}
}

auto SignalBase::connect(Connection* x) -> void
{
	this->slots.emplace_back(x);
}

auto SignalBase::disconnect(Connection* x) -> void
{
	std::erase(this->slots, x);
}

auto SignalBase::connected(const Connection* x) const -> bool
{
	return std::ranges::any_of(this->slots, [x](auto s) { return x == s; });
}
