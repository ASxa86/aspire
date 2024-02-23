#include <aspire/test/Kernel.h>

using aspire::Kernel;

namespace
{
	Kernel* KernelInstance{nullptr};
}

auto Kernel::Instance() -> Kernel*
{
	return KernelInstance;
}

Kernel::Kernel()
{
	if(KernelInstance == nullptr)
	{
		KernelInstance = this;
	}
}

Kernel::~Kernel()
{
	KernelInstance = nullptr;
}

auto Kernel::run() -> int
{
	return 0;
}
