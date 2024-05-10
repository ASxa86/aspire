#pragma once

#include <aspire/core/Object.h>
#include <aspire/core/Pimpl.h>
#include <aspire/core/Service.h>
#include <aspire/core/export.hxx>

namespace aspire::core
{
	class ASPIRE_CORE_EXPORT Kernel : public Object
	{
	public:
		Kernel();
		~Kernel() override;

		Kernel(const Kernel&) = delete;
		auto operator=(const Kernel&) = delete;

		Kernel(Kernel&&) noexcept = delete;
		auto operator=(Kernel&&) noexcept = delete;

		auto addService(std::unique_ptr<Service> x) -> void;

		auto sendEvent(Event& x, Object* receiver) -> void;
		auto queueEvent(std::unique_ptr<Event> x, Object* receiver) -> void;

		auto run() -> int;
		auto quit() -> void;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}