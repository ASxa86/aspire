#include <aspire/core/Kernel.h>
#include <aspire/core/Timer.h>

using aspire::Timer;

auto Timer::start() -> void
{
	auto* kernel = Kernel::Instance();
	kernel->addTimer(this, this->interval);
}

auto Timer::stop() -> void
{
	auto* kernel = Kernel::Instance();
	kernel->removeTimer(this);
}

auto Timer::setInterval(std::chrono::steady_clock::duration x) noexcept -> void
{
	this->interval = x;
}

auto Timer::getInterval() const noexcept -> std::chrono::steady_clock::duration
{
	return this->interval;
}

auto Timer::eventTimer(EventTimer*) -> void override
{
	this->timeout.emit();
}