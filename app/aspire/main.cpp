#include <aspire/core/Kernel.h>
#include <aspire/scene/Window.h>

auto main() -> int
{
	constexpr auto defaultX{80};
	constexpr auto defaultY{80};
	constexpr auto defaultWidth{1280};
	constexpr auto defaultHeight{720};

	aspire::core::Kernel kernel;

	auto window = std::make_unique<aspire::scene::Window>();
	window->setX(defaultX);
	window->setY(defaultY);
	window->setWidth(defaultWidth);
	window->setHeight(defaultHeight);
	window->setTitle("Aspire");
	kernel.addService(std::move(window));

	return kernel.run();
}