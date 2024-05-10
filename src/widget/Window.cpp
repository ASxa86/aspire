#include <aspire/widget/Window.h>

#include <aspire/core/Kernel.h>
#include <aspire/core/PimplImpl.h>
#include <aspire/render/Window.h>
#include <mutex>
#include <thread>

using aspire::widget::Window;

struct Window::Impl
{
	std::jthread renderThread;

	std::mutex renderThreadMutex;
	aspire::render::Window renderer;
	std::unique_ptr<Widget> widget;
	aspire::core::Kernel* kernel{};

	std::string title;
	int x{};
	int y{};
	int width{};
	int height{};
};

Window::Window() = default;

Window::~Window()
{
	this->pimpl->renderThread.request_stop();

	if(this->pimpl->renderThread.joinable())
	{
		this->pimpl->renderThread.join();
	}
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
	// Synchronize main thread with render thread.
	std::scoped_lock lock(this->pimpl->renderThreadMutex);

	if(!this->pimpl->renderer.valid())
	{
		return;
	}
}

auto Window::onStartup() -> void
{
	this->pimpl->kernel = dynamic_cast<aspire::core::Kernel*>(this->getParent());

	if(this->pimpl->kernel == nullptr)
	{
		return;
	}

	this->pimpl->renderer.handleEvent(
		[this](aspire::render::EventWindow x)
		{
			switch(x.type)
			{
				case aspire::render::EventWindow::Type::Close:
					this->pimpl->kernel->queueEvent(std::make_unique<aspire::core::Event>(aspire::core::Event::Type::Close), this);
					break;

				default:
					break;
			}
		});

	this->pimpl->renderThread = std::jthread(
		[this](auto stopToken)
		{
			// Initialize the window, surface, and graphics context on the render thread.
			{
				std::scoped_lock lock(this->pimpl->renderThreadMutex);
				this->pimpl->renderer.setX(this->pimpl->x);
				this->pimpl->renderer.setY(this->pimpl->y);
				this->pimpl->renderer.setWidth(this->pimpl->width);
				this->pimpl->renderer.setHeight(this->pimpl->height);
				this->pimpl->renderer.setTitle(this->pimpl->title);
				this->pimpl->renderer.create();

				// Exit the thread if renderer failed to create.
				if(!this->pimpl->renderer.valid())
				{
					this->pimpl->renderThread.request_stop();
				}
			}

			while(!stopToken.stop_requested())
			{
				if(this->pimpl->widget)
				{
					// Handle updating the scene graph on the render thread. This should be queued widgets that get added via an ::update() or
					// dirty() invocation. Not all widgets.
					for(const auto& widget : this->pimpl->widget->getChildren())
					{
						(void)widget;
					}
				}

				// Synchronize with the main thread (Window::frame).
				std::scoped_lock lock(this->pimpl->renderThreadMutex);
				this->pimpl->renderer.frame();
			}
		});
}