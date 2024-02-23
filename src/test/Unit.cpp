#include <aspire/test/Unit.h>

using aspire::Unit;

Unit::Unit(std::function<void()> x) : test{std::move(x)}
{
}

auto Unit::run() -> void
{
	if(this->test)
	{
		this->test();
	}
}

auto Unit::getResult() const noexcept -> bool
{
	return this->result;
}