#include <aspire/core/EventTimer.h>
#include <aspire/core/Kernel.h>

using aspire::Kernel;

Kernel* Kernel::Self = nullptr;

auto Kernel::Instance() noexcept -> Kernel*
{
	return Kernel::Self;
}

auto Kernel::SendEvent(Object* receiver, Event* x)
{
	if(receiver == nullptr)
	{
		return;
	}

	receiver->event(x);
}

Kernel::Kernel()
{
	if(Kernel::Self == nullptr)
	{
		Kernel::Self = this;
	}
}

Kernel::~Kernel()
{
	Kernel::Self = nullptr;
}

auto Kernel::run() -> int
{
	this->running = true;

	this->initialize();

	this->start = std::chrono::steady_clock::now();

	while(this->running == true)
	{
		const auto elapsed = std::chrono::steady_clock::now() - this->start;

		for(auto& timer : this->timers)
		{
			if(timer.interval == std::chrono::steady_clock::duration::zero())
			{
				EventTimer e{};
				Kernel::SendEvent(timer.object, &e);
				continue;
			}

			static constexpr auto limit{5};
			timer.accumulate += elapsed;

			while(timer.accumulate > timer.interval && timer.count < limit)
			{
				timer.accumulate -= timer.interval;

				EventTimer e{};
				Kernel::SendEvent(timer.object, &e);

				timer.count++;
			}

			timer.count = 0;
		}

		this->start = std::chrono::steady_clock::now();
	}

	this->terminate();

	return EXIT_SUCCESS;
}

auto Kernel::quit() -> void
{
	this->running = false;
}

auto Kernel::addTimer(Object* x, std::chrono::steady_clock::duration interval) -> void
{
	Timer timer{};
	timer.object = x;
	timer.interval = interval;
	this->timers.emplace_back(timer);
}

auto Kernel::removeTimer(Object* x) -> void
{
	std::erase_if(this->timers, [x](const auto& t) { return t.object == x; });
}
