#include <aspire/core/Kernel.h>
#include <aspire/gui/Window.h>

int main()
{
	aspire::Kernel kernel{};

	auto* window = kernel.addChild<aspire::Window>();
	window->setWidth(1280);
	window->setHeight(720);
	window->setTitle("Aspire");

	return kernel.run();
}
