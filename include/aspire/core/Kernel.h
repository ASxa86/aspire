#pragma once

#include <aspire/core/Object.h>
#include <aspire/core/Pimpl.h>
#include <aspire/core/export.hxx>

namespace aspire::core
{
	class ASPIRE_CORE_EXPORT Kernel : public Object
	{
	public:
		enum class FrameGroup : sigslot::group_id
		{
			Service,
			Object
		};

		static constexpr std::chrono::milliseconds FrameFixedRate{10};
		static auto Instance() -> Kernel*;

		Kernel();
		~Kernel() override;

		Kernel(const Kernel&) = delete;
		auto operator=(const Kernel&) = delete;

		Kernel(Kernel&&) noexcept = delete;
		auto operator=(Kernel&&) noexcept = delete;

		auto sendEvent(Event& x, Object* receiver) -> void;
		auto queueEvent(std::unique_ptr<Event> x, Object* receiver) -> void;
		auto onFrame(std::function<void()> x, FrameGroup group) -> sigslot::connection;
		auto onFrameFixed(std::function<void()> x, FrameGroup group) -> sigslot::connection;

		auto run() -> int;
		auto quit() -> void;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}