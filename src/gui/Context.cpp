#include <aspire/gui/Context.h>

using aspire::Context;

auto Context::setSurface(const Surface& x) -> void
{
	this->surface = x;
}

auto Context::getSurface() const -> const Surface&
{
	return this->surface;
}
