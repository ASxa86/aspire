#pragma once

#include <aspire/core/Object.h>

namespace aspire
{
	class ASPIRE_CORE_EXPORT Timer : public Object
	{
	public:
		auto start() -> void;
		auto stop() -> void;
		auto setInterval(std::chrono::steady_clock::duration x) noexcept -> void;
		auto getInterval() const noexcept -> std::chrono::steady_clock::duration;

		Signal<void()> timeout;

	private:
		auto eventTimer(EventTimer*) -> void override;
		std::chrono::steady_clock::duration interval{};
	};
}