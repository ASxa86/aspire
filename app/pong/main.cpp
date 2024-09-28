#include <aspire/core/Kernel.h>
#include <aspire/scene/Node.h>

auto main() -> int
{
	aspire::core::Kernel kernel;

	auto root = std::make_unique<aspire::scene::Node>();

	return kernel.run();
}