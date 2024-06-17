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

	auto rect = root->createChild<aspire::scene::Rectangle>();
	rect->setPosition({80, 80});
	rect->setSize({64, 64});
	rect->onFrameFixed(
		[rect]
		{
			auto pos = rect->getPosition();
			pos.x += 0.01;
			rect->setPosition(pos);
		});

	auto subrect = rect->createChild<aspire::scene::Rectangle>();
	subrect->setSize({16, 16});
	subrect->setColor(sf::Color::Red);
	subrect->setRotation(30);

	subrect->onFrame(
		[subrect]
		{
			auto rot = subrect->getRotation();
			rot += 0.01;
			subrect->setRotation(rot);
		});

	window->setRootNode(std::move(root));

	// Add the window last to ensure frame processing occurs last.
	kernel.addChild(std::move(window));

	return kernel.run();
}