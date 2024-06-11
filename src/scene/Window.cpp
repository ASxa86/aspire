#include <aspire/scene/Window.h>

#include <aspire/core/Kernel.h>
#include <aspire/core/PimplImpl.h>
#include <SFML/Graphics.hpp>

using aspire::core::Event;
using aspire::core::Kernel;
using aspire::scene::Window;

struct Window::Impl
{
	sf::RenderWindow renderer;
	sf::Color clearColor{static_cast<sf::Uint8>(0.2F * 255U), static_cast<sf::Uint8>(0.3F * 255U), static_cast<sf::Uint8>(0.3F * 255U),
						 static_cast<sf::Uint8>(1.0F * 255U)};

	std::unique_ptr<Node> rootNode;

	std::string title;
	int x{};
	int y{};
	int width{};
	int height{};
};

Window::Window()
{
	// Connect on startup to preserve object order when processing frames.
	this->onStartup(
		[this]()
		{
			if(this->pimpl->rootNode == nullptr)
			{
				Kernel::Instance()->quit();
				return;
			}

			this->onFrame([this]() { this->frame(); });

			constexpr auto style = sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close;
			const auto width = static_cast<unsigned int>(this->pimpl->width);
			const auto height = static_cast<unsigned int>(this->pimpl->height);
			sf::ContextSettings settings;
			settings.antialiasingLevel = 4;
			this->pimpl->renderer.create(sf::VideoMode{width, height}, this->pimpl->title, style, settings);
			this->pimpl->renderer.setPosition({this->pimpl->x, this->pimpl->y});
		});
}

Window::~Window() = default;

auto Window::setX(int x) noexcept -> void
{
	this->pimpl->x = x;
}

auto Window::getX() const noexcept -> int
{
	return this->pimpl->x;
}

auto Window::setY(int x) noexcept -> void
{
	this->pimpl->y = x;
}

auto Window::getY() const noexcept -> int
{
	return this->pimpl->y;
}

auto Window::setHeight(int x) noexcept -> void
{
	this->pimpl->height = x;
}

auto Window::getHeight() const noexcept -> int
{
	return this->pimpl->height;
}

auto Window::setWidth(int x) noexcept -> void
{
	this->pimpl->width = x;
}

auto Window::getWidth() const noexcept -> int
{
	return this->pimpl->width;
}

auto Window::setRootNode(std::unique_ptr<Node> x) -> void
{
	this->pimpl->rootNode = std::move(x);
}

auto Window::getRootNode() const -> Node*
{
	return this->pimpl->rootNode.get();
}

auto Window::setTitle(std::string_view x) -> void
{
	this->pimpl->title = x;
}

auto Window::getTitle() const -> std::string_view
{
	return this->pimpl->title;
}

auto Window::setColor(sf::Color x) noexcept -> void
{
	this->pimpl->clearColor = x;
}

auto Window::getColor() const noexcept -> sf::Color
{
	return this->pimpl->clearColor;
}

auto Window::event(aspire::core::Event* x) -> void
{
	switch(x->type())
	{
		case aspire::core::Event::Type::Close:
			Kernel::Instance()->quit();
			break;

		default:
			break;
	}
}

auto Window::frame() -> void
{
	if(this->pimpl->renderer.isOpen() == false)
	{
		return;
	}

	sf::Event e{};
	while(this->pimpl->renderer.pollEvent(e) == true)
	{
		switch(e.type)
		{
			case sf::Event::EventType::Closed:
			{
				Event evt{Event::Type::Close};
				Kernel::Instance()->sendEvent(evt, this);
			}
			break;

			case sf::Event::EventType::Resized:
			{
				Event evt{Event::Type::Resize};
				Kernel::Instance()->sendEvent(evt, this);
			}
			break;

			default:
				break;
		}
	}

	this->pimpl->renderer.clear(this->pimpl->clearColor);
	this->pimpl->rootNode->draw(this->pimpl->renderer);
	this->pimpl->renderer.display();
}
