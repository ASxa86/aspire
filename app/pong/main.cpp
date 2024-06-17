#include <aspire/core/Kernel.h>
#include <aspire/scene/Rectangle.h>
#include <aspire/scene/Window.h>
#include "Paddle.h"

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
	window->setColor(sf::Color::Black);

	auto root = std::make_unique<aspire::scene::Node>();

	Paddle player{*root};
	player.setPosition({150, defaultHeight / 2.0});
	player.setSize({50, 150});

	Paddle paddle{*root};

	paddle.setPosition({defaultWidth - 150, defaultHeight / 2.0});
	paddle.setSize({50, 150});

	window->setRootNode(std::move(root));

	// Add the window last to ensure frame processing occurs last.
	kernel.addChild(std::move(window));

	return kernel.run();
}