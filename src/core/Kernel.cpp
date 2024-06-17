#include <aspire/core/Kernel.h>

#include <aspire/core/PimplImpl.h>
#include <chrono>
#include <deque>
#include <iostream>
#include <mutex>
#include <numeric>

using aspire::core::Kernel;

struct Kernel::Impl
{
	sigslot::signal<> frame;
	sigslot::signal<> frameFixed;
	std::vector<std::pair<std::unique_ptr<Event>, Object*>> events;
	std::mutex mutexEvent;
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::duration elapsed{};
	std::chrono::steady_clock::duration accumulate{};
	static inline Kernel* Instance{nullptr};
	bool running{false};
};

Kernel* Kernel::Instance()
{
	return Kernel::Impl::Instance;
}

Kernel::Kernel()
{
	if(Kernel::Impl::Instance != nullptr)
	{
		return;
	}

	Kernel::Impl::Instance = this;
}

Kernel::~Kernel()
{
	Kernel::Impl::Instance = nullptr;
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

auto Kernel::onFrame(std::function<void()> x) -> sigslot::connection
{
	return this->pimpl->frame.connect(std::move(x));
}

auto Kernel::onFrameFixed(std::function<void()> x) -> sigslot::connection
{
	return this->pimpl->frameFixed.connect(std::move(x));
}

auto Kernel::run() -> int
{
	this->pimpl->running = true;

	// Process all initialized objects.
	this->startup();

	this->pimpl->start = std::chrono::steady_clock::now();

	std::deque<std::chrono::steady_clock::duration> frames;

	while(this->pimpl->running == true)
	{
		const auto frameStart = std::chrono::steady_clock::now();

		const auto elapsed = frameStart - this->pimpl->start;
		this->pimpl->elapsed += elapsed;
		this->pimpl->accumulate += elapsed;
		this->pimpl->start = frameStart;

		{
			std::scoped_lock lock(this->pimpl->mutexEvent);

			for(auto&& [event, receiver] : this->pimpl->events)
			{
				this->sendEvent(*event, receiver);
			}
		}

		auto count = 0;

		while(this->pimpl->accumulate >= Kernel::FrameFixedRate && count < 5)
		{
			this->pimpl->accumulate -= Kernel::FrameFixedRate;
			this->pimpl->frameFixed();
			count++;
		}

		this->pimpl->frame();

		frames.emplace_back(elapsed);

		if(frames.size() > 1000)
		{
			frames.pop_front();
		}
	}

	std::cout << "Frames: " << frames.size() << "\n";

	if(frames.empty() == false)
	{
		const auto sum = std::accumulate(std::begin(frames), std::end(frames), std::chrono::steady_clock::duration::zero());
		const auto avg = std::chrono::duration_cast<std::chrono::duration<double>>(sum).count() / static_cast<double>(frames.size());
		const auto fps = 1.0 / avg;

		std::cout << "Interval: " << avg << " s\n";
		std::cout << "FPS: " << fps << " Hz\n";
	}

	return EXIT_SUCCESS;
}

auto Kernel::quit() -> void
{
	this->pimpl->running = false;
}
