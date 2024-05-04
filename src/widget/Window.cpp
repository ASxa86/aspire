#include <aspire/widget/Window.h>

#include <aspire/core/PimplImpl.h>
#include <aspire/render/Window.h>
#include <mutex>
#include <thread>

using aspire::widget::Window;

struct Window::Impl
{
	~Impl()
	{
		if(this->renderThread.joinable())
		{
			this->renderThread.join();
		}
	}

	std::thread renderThread;
	std::mutex renderThreadMutex;
	aspire::render::Window renderer;
	std::unique_ptr<Widget> widget;

	std::string title;
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

auto Window::frame() -> void
{
	// Synchronize main thread with render thread.
	std::scoped_lock lock(this->pimpl->renderThreadMutex);

	if(this->pimpl->renderer.valid() == false)
	{
		return;
	}

	for(const auto& widget : this->pimpl->widget->getChildren())
	{
		(void)widget;
	}
}

auto Window::onStartup() -> void
{
	this->pimpl->renderThread = std::thread(
		[this]
		{
			auto valid{false};

			{
				std::scoped_lock lock(this->pimpl->renderThreadMutex);
				this->pimpl->renderer.setX(this->pimpl->x);
				this->pimpl->renderer.setY(this->pimpl->y);
				this->pimpl->renderer.setWidth(this->pimpl->width);
				this->pimpl->renderer.setHeight(this->pimpl->height);
				this->pimpl->renderer.setTitle(this->pimpl->title);
				this->pimpl->renderer.create();
				valid = this->pimpl->renderer.valid();
			}

			while(valid)
			{
				// Block until the main thread has freed itself.
				std::scoped_lock lock(this->pimpl->renderThreadMutex);
				this->pimpl->renderer.frame();
			}
		});
}