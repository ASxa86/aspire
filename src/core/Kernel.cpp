#include <aspire/core/Kernel.h>

#include <aspire/core/PimplImpl.h>
#include <chrono>
#include <iostream>
#include <mutex>
#include <numeric>

using aspire::core::Kernel;
using aspire::core::Service;

struct Kernel::Impl
{
	std::vector<Service*> services;
	std::vector<std::pair<std::unique_ptr<Event>, Object*>> events;
	std::mutex mutexEvent;
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::duration elapsed{};
	bool running{false};
};

Kernel::Kernel() = default;
Kernel::~Kernel() = default;

auto Kernel::addService(std::unique_ptr<Service> x) -> void
{
	this->pimpl->services.emplace_back(x.get());
	this->addChild(std::move(x));
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
auto Kernel::sendEvent(Event& x, Object* receiver) -> void
{
	receiver->event(&x);
}

auto Kernel::queueEvent(std::unique_ptr<Event> x, Object* receiver) -> void
{
	std::scoped_lock lock(this->pimpl->mutexEvent);
	this->pimpl->events.emplace_back(std::move(x), receiver);
}

auto Kernel::run() -> int
{
	// Process all initialized objects.
	this->startup();

	this->pimpl->running = true;
	this->pimpl->start = std::chrono::steady_clock::now();

	std::vector<std::chrono::steady_clock::duration> frames;

	while(this->pimpl->running)
	{
		const auto frameStart = std::chrono::steady_clock::now();

		this->pimpl->elapsed += std::chrono::steady_clock::now() - this->pimpl->start;

		{
			std::scoped_lock lock(this->pimpl->mutexEvent);

			for(auto&& [event, receiver] : this->pimpl->events)
			{
				this->sendEvent(*event, receiver);
			}
		}

		for(auto* service : this->pimpl->services)
		{
			service->frame();
		}

		frames.emplace_back(std::chrono::steady_clock::now() - frameStart);
	}

	std::cout << "Frames: " << frames.size() << "\n";

	const auto sum = std::accumulate(std::begin(frames), std::end(frames), std::chrono::steady_clock::duration::zero());
	const auto avg = std::chrono::duration_cast<std::chrono::duration<double>>(sum).count() / static_cast<double>(frames.size());
	const auto fps = 1.0 / avg;

	std::cout << "Interval: " << avg << " s\n";
	std::cout << "FPS: " << fps << " Hz\n";

	return EXIT_SUCCESS;
}

auto Kernel::quit() -> void
{
	this->pimpl->running = false;
}
