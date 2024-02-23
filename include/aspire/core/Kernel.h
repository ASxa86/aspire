#pragma once

#include <aspire/core/Object.h>

namespace aspire
{
	class ASPIRE_CORE_EXPORT Kernel : public Object
	{
	public:
		static auto Instance() noexcept -> Kernel*;
		static auto SendEvent(Object* receiver, Event* x);

		Kernel();
		~Kernel();

		auto run() -> int;
		auto quit() -> void;

		auto addTimer(Object* x, std::chrono::steady_clock::duration interval) -> void;
		auto removeTimer(Object* x) -> void;

	private:
		static Kernel* Self;

		struct Timer
		{
			Object* object{nullptr};
			std::chrono::steady_clock::duration accumulate{};
			std::chrono::steady_clock::duration interval{};
			int count{};
		};

		std::vector<Timer> timers;
		std::chrono::steady_clock::time_point start{};
		std::chrono::steady_clock::duration elapsed{};
		bool running{false};
	};
}
