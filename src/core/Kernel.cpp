#include <aspire/core/Kernel.h>

#include <aspire/core/PimplImpl.h>

using aspire::core::Kernel;
using aspire::core::Service;

struct Kernel::Impl
{
	std::vector<Service*> services;
};

Kernel::Kernel() = default;
Kernel::~Kernel() = default;

auto Kernel::addService(std::unique_ptr<Service> x) -> void
{
	this->pimpl->services.emplace_back(x.get());
	this->addChild(std::move(x));
}

auto Kernel::run() -> int
{
	// Process all initialized objects.
	this->startup();

	for(auto* service : this->pimpl->services)
	{
		service->frame();
	}

	return EXIT_SUCCESS;
}
