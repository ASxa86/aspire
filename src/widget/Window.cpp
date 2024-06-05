#include <aspire/widget/Window.h>

#include <aspire/core/Kernel.h>
#include <aspire/core/PimplImpl.h>
#include <SFML/Graphics.hpp>
#include <mutex>
#include <thread>

using aspire::core::Event;
using aspire::widget::Window;

struct Window::Impl
{
	~Impl()
	{
		this->stopToken = true;

		if(this->renderThread.joinable() == true)
		{
			this->renderThread.join();
		}
	}

	std::thread renderThread;
	std::atomic<bool> stopToken{};
	std::mutex renderMutex;
	sf::RenderWindow renderer{};
	sf::Color clearColor{};

	std::unique_ptr<Widget> widget;
	aspire::core::Kernel* kernel{};

	std::string title;
	Color color{.r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.0f};
	int x{};
	int y{};
	int width{};
	int height{};
};

Window::Window() = default;

Window::~Window()
{
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

	std::scoped_lock lock(this->pimpl->renderMutex);

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

	// Deactivate context to enable rendering on a different thread.
	this->pimpl->renderer.setActive(false);

	this->pimpl->renderThread = std::thread(
		[this]
		{
			// Re-enable context to run on this graphics thread.
			this->pimpl->renderer.setActive(true);

			while(this->pimpl->stopToken == false)
			{
				{
					std::scoped_lock lock(this->pimpl->renderMutex);
					this->synchronize();
				}

				this->pimpl->renderer.clear(this->pimpl->clearColor);
				this->pimpl->renderer.display();
			}
		});
}

auto Window::synchronize() -> void
{
	this->pimpl->clearColor.r = static_cast<sf::Uint8>(this->pimpl->color.r * 255);
	this->pimpl->clearColor.g = static_cast<sf::Uint8>(this->pimpl->color.g * 255);
	this->pimpl->clearColor.b = static_cast<sf::Uint8>(this->pimpl->color.b * 255);
	this->pimpl->clearColor.a = static_cast<sf::Uint8>(this->pimpl->color.a * 255);

	// this->pimpl->renderer.setPosition({this->pimpl->x, this->pimpl->y});
	// Bug // Sizing needs to occur on main thread but the view is also computed which needs to occur on the render thread.
	// this->pimpl->renderer.setSize({static_cast<unsigned int>(this->pimpl->width), static_cast<unsigned int>(this->pimpl->height)});

	if(this->pimpl->widget == nullptr)
	{
		return;
	}

	this->synchronize(*this->pimpl->widget);
}

auto Window::synchronize(Widget& x) -> void
{
	for(auto* widget : x.childWidgets())
	{
		this->synchronize(*widget);
	}
}