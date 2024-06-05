#include <aspire/widget/Window.h>

#include <aspire/core/Kernel.h>
#include <aspire/core/PimplImpl.h>
#include <SFML/Graphics.hpp>
#include "BatchRenderer.h"

using aspire::core::Event;
using aspire::widget::Window;

struct Window::Impl
{
	sf::RenderWindow renderer;
	BatchRenderer batchRenderer{};
	sf::Color clearColor;

	std::unique_ptr<Widget> widget;
	aspire::core::Kernel* kernel{};

	std::string title;
	Color color{.r = 0.2F, .g = 0.3F, .b = 0.3F, .a = 1.0F};
	int x{};
	int y{};
	int width{};
	int height{};
};

Window::Window() = default;
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

auto Window::setWidget(std::unique_ptr<Widget> x) -> void
{
	this->pimpl->widget = std::move(x);
}

auto Window::getWidget() const -> Widget*
{
	return this->pimpl->widget.get();
}

auto Window::setTitle(std::string_view x) -> void
{
	this->pimpl->title = x;
}

auto Window::getTitle() const -> std::string_view
{
	return this->pimpl->title;
}

auto Window::setColor(Color x) noexcept -> void
{
	this->pimpl->color = x;
}

auto Window::getColor() const noexcept -> Color
{
	return this->pimpl->color;
}

auto Window::event(aspire::core::Event* x) -> void
{
	switch(x->type())
	{
		case aspire::core::Event::Type::Close:
			this->pimpl->kernel->quit();
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
				this->pimpl->kernel->sendEvent(evt, this);
			}
			break;

			case sf::Event::EventType::Resized:
			{
				Event evt{Event::Type::Resize};
				this->pimpl->kernel->sendEvent(evt, this);
			}
			break;

			default:
				break;
		}
	}

	// Sort, batch, update nodes, etc...
	this->update();

	this->pimpl->renderer.clear(this->pimpl->clearColor);
	this->pimpl->renderer.draw(this->pimpl->batchRenderer);
	this->pimpl->renderer.display();
}

auto Window::onStartup() -> void
{
	this->pimpl->kernel = dynamic_cast<aspire::core::Kernel*>(this->getParent());

	if(this->pimpl->kernel == nullptr)
	{
		return;
	}

	constexpr auto style = sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close;
	const auto width = static_cast<unsigned int>(this->pimpl->width);
	const auto height = static_cast<unsigned int>(this->pimpl->height);
	this->pimpl->renderer.create(sf::VideoMode{width, height}, this->pimpl->title, style);
	this->pimpl->renderer.setPosition({this->pimpl->x, this->pimpl->y});
}

auto Window::update() -> void
{
	constexpr auto maxUint8 = std::numeric_limits<sf::Uint8>::max();
	this->pimpl->clearColor.r = static_cast<sf::Uint8>(this->pimpl->color.r * maxUint8);
	this->pimpl->clearColor.g = static_cast<sf::Uint8>(this->pimpl->color.g * maxUint8);
	this->pimpl->clearColor.b = static_cast<sf::Uint8>(this->pimpl->color.b * maxUint8);
	this->pimpl->clearColor.a = static_cast<sf::Uint8>(this->pimpl->color.a * maxUint8);

	if(this->pimpl->widget == nullptr)
	{
		return;
	}

	this->update(*this->pimpl->widget);

	// I'll have an updated list of nodes.
	// Sort and add to batch renderer.
	// this->pimpl->batchRenderer.add(node);
}

auto Window::update(Widget& x) -> void
{
	for(auto* widget : x.childWidgets())
	{
		this->update(*widget);
	}
}