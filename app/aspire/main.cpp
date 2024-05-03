#include <aspire/core/Kernel.h>
#include <aspire/widget/Window.h>

auto main() -> int
{
	aspire::core::Kernel kernel;

	auto window = std::make_unique<aspire::widget::Window>();
	window->setX(80);
	window->setY(80);
	window->setWidth(1280);
	window->setHeight(720);
	kernel.addService(std::move(window));

	return kernel.run();
}