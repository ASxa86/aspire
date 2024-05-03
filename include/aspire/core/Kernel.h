#pragma once

#include <aspire/core/Object.h>
#include <aspire/core/Service.h>
#include <aspire/core/export.hxx>
#include <aspire/core/Pimpl.h>

namespace aspire::core
{
	class ASPIRE_CORE_EXPORT Kernel : public Object
	{
	public:
		Kernel();
		~Kernel() override;

		auto addService(std::unique_ptr<Service> x) -> void;
		auto run() -> int;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}