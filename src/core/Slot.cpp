#include <aspire/core/Signal.h>
#include <aspire/core/Slot.h>

using aspire::Connection;

Connection::Connection(impl::SignalBase& x) : signal{&x}
{
}

Connection::~Connection()
{
	this->disconnect();
}

auto Connection::disconnect() -> void
{
	if(this->connected() == true)
	{
		this->signal->disconnect(this);
	}
}

auto Connection::connected() const -> bool
{
	return this->signal->connected(this);
}
