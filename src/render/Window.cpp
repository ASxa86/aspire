#include <aspire/render/Window.h>

#include <aspire/core/PimplImpl.h>
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

using aspire::render::EventMouse;
using aspire::render::EventWindow;
using aspire::render::Window;

namespace
{
	template <class... Ts>
	struct EventHandler : Ts...
	{
		using Ts::operator()...;
	};

	auto ConvertEventSFtoAspire(Window* window, const sf::Event& x) -> void
	{
		aspire::render::Event event;

		switch(x.type)
		{
			case sf::Event::EventType::Closed:
			{
				EventWindow evt;
				evt.type = EventWindow::Type::Close;
				evt.height = x.size.height;
				evt.width = x.size.width;
				event = evt;
			}
			break;

			case sf::Event::EventType::MouseMoved:
			{
				EventMouse evt;
				evt.type = EventMouse::Type::Move;
				evt.x = x.mouseMove.x;
				evt.y = x.mouseMove.y;
				event = evt;
			}
			break;

			default:
				break;
		}

		// No value was assigned to the event variant so lets exit early.
		if(event.index() == 0)
		{
			return;
		}

		window->addEvent(event);
	}

	auto ConvertArrayToSFColor(std::array<float, 4> x) -> sf::Color
	{
		return {static_cast<sf::Uint8>(x[0] * 255), static_cast<sf::Uint8>(x[1] * 255), static_cast<sf::Uint8>(x[2] * 255),
				static_cast<sf::Uint8>(x[3] * 255)};
	}
}

struct Window::Impl
{
	sf::RenderWindow window{};

	std::vector<Event> events;

	// Default initialize event handlers to do nothing. This is being done to save an extra if check
	// on valid functions everytime the events get processed.
	std::function<void(EventWindow)> handleEventWindow{[](auto) {}};
	std::function<void(EventMouse)> handleEventMouse{[](auto) {}};

	std::string title;
	std::array<float, 4> clearColor{0.2f, 0.3f, 0.3f, 1.0f};
	int x{};
	int y{};
	int width{};
	int height{};
	bool valid{false};
};

Window::Window() noexcept = default;
Window::~Window() = default;

auto Window::setTitle(std::string_view x) -> void
{
	this->pimpl->title = x;
}

auto Window::getTitle() const -> std::string_view
{
	return this->pimpl->title;
}

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

auto Window::setClearColor(std::array<float, 4> x) noexcept -> void
{
	this->pimpl->clearColor = x;
}

auto Window::getClearColor() const noexcept -> std::array<float, 4>
{
	return this->pimpl->clearColor;
}

auto Window::addEvent(Event x) -> void
{
	this->pimpl->events.emplace_back(x);
}

auto Window::handleEvent(std::function<void(EventWindow)> x) -> void
{
	this->pimpl->handleEventWindow = std::move(x);
}

auto Window::handleEvent(std::function<void(EventMouse)> x) -> void
{
	this->pimpl->handleEventMouse = std::move(x);
}

auto Window::create() -> void
{
	constexpr auto style = sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize;
	this->pimpl->window.create(sf::VideoMode{static_cast<unsigned int>(this->pimpl->width), static_cast<unsigned int>(this->pimpl->height)},
							   this->pimpl->title, style);
}

auto Window::destroy() -> void
{
	this->pimpl->window.close();
}

auto Window::valid() noexcept -> bool
{
	return this->pimpl->window.isOpen();
}

auto Window::frame() -> void
{
	// Process events
	for(auto event : this->pimpl->events)
	{
		std::visit(EventHandler{[](auto) {}, this->pimpl->handleEventWindow, this->pimpl->handleEventMouse}, event);
	}

	this->pimpl->events.clear();

	this->pimpl->window.clear(ConvertArrayToSFColor(this->pimpl->clearColor));

	this->pimpl->window.display();

	sf::Event e{};
	while(this->pimpl->window.pollEvent(e))
	{
		ConvertEventSFtoAspire(this, e);
	}
}
