#include <aspire/core/Kernel.h>
#include <aspire/scene/Rectangle.h>
#include <aspire/scene/Window.h>
#include "Paddle.h"

auto main() -> int
{
	aspire::core::Kernel kernel;

	auto root = std::make_unique<aspire::scene::Node>();

	auto* window = kernel.createChild<aspire::scene::Window>();

	Paddle player{*root};
	player.setPosition({150.0F, static_cast<float>(window->getHeight()) / 2.0F});
	player.setSize({50.0F, 150.0F});

	Paddle paddle{*root};

	paddle.setPosition({window->getWidth() - 150.0F, static_cast<float>(window->getHeight()) / 2.0F});
	paddle.setSize({50.0F, 150.0F});

	window->setRootNode(std::move(root));

	return kernel.run();
}