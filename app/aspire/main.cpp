#include <aspire/core/Kernel.h>
#include <aspire/scene/Rectangle.h>
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
	window->setColor(sf::Color::Green);

	auto root = std::make_unique<aspire::scene::Node>();

	auto rect = std::make_unique<aspire::scene::Rectangle>();
	rect->setPosition({80, 80});
	rect->setSize({64, 64});

	auto subrect = std::make_unique<aspire::scene::Rectangle>();
	subrect->setSize({16, 16});
	subrect->setColor(sf::Color::Red);
	subrect->setRotation(30);
	rect->addChild(std::move(subrect));

	root->addChild(std::move(rect));
	window->setRootNode(std::move(root));

	kernel.addService(std::move(window));

	return kernel.run();
}