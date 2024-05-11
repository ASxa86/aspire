#include <aspire/render/Window.h>

#include <aspire/core/PimplImpl.h>
#include <vulkan/vulkan.h>
#include <vector>
#include "VulkanInstance.h"

#include <GLFW/glfw3.h>

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

	auto GetWindow(GLFWwindow* x) -> Window*
	{
		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
		return reinterpret_cast<Window*>(glfwGetWindowUserPointer(x));
	}

	auto CallbackWindowClose(GLFWwindow* glfw) -> void
	{
		auto* window = GetWindow(glfw);

		EventWindow event;
		event.type = EventWindow::Type::Close;
		window->addEvent(event);
	}

	// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
	auto CallbackMousePos(GLFWwindow* glfw, double x, double y) -> void
	{
		auto* window = GetWindow(glfw);

		EventMouse event;
		event.x = x;
		event.y = y;
		event.type = EventMouse::Type::Move;
		window->addEvent(event);
	}

	// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
	auto CallbackMouseButton(GLFWwindow* glfw, int button, int action, int /*unused*/) -> void
	{
		auto* window = GetWindow(glfw);

		double x{};
		double y{};
		glfwGetCursorPos(glfw, &x, &y);

		EventMouse event;
		event.x = x;
		event.y = y;

		switch(button)
		{
			case GLFW_MOUSE_BUTTON_LEFT:
				event.button = EventMouse::Button::Left;
				break;

			case GLFW_MOUSE_BUTTON_MIDDLE:
				event.button = EventMouse::Button::Middle;
				break;

			case GLFW_MOUSE_BUTTON_RIGHT:
				event.button = EventMouse::Button::Right;
				break;

			default:
				break;
		}

		switch(action)
		{
			case GLFW_PRESS:
				event.type = EventMouse::Type::Press;
				break;

			case GLFW_RELEASE:
				event.type = EventMouse::Type::Release;
				break;

			default:
				break;
		}

		window->addEvent(event);
	}
}

struct Window::Impl
{
	GLFWwindow* window{};
	VulkanInstance vulkanInstance;

	std::vector<Event> events;

	// Default initialize event handlers to do nothing. This is being done to save an extra if check
	// on valid functions everytime the events get processed.
	std::function<void(EventWindow)> handleEventWindow{[](auto) {}};
	std::function<void(EventMouse)> handleEventMouse{[](auto) {}};

	std::string title;
	int x{};
	int y{};
	int width{};
	int height{};
	bool valid{false};
};

Window::Window() = default;
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
	if(glfwInit() == GLFW_FALSE)
	{
		return;
	}

	if(glfwVulkanSupported() == GLFW_FALSE)
	{
		return;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	this->pimpl->window = glfwCreateWindow(this->pimpl->width, this->pimpl->height, this->pimpl->title.c_str(), nullptr, nullptr);

	if(this->pimpl->window == nullptr)
	{
		glfwTerminate();
		return;
	}

	glfwSetWindowUserPointer(this->pimpl->window, this);
	glfwSetWindowCloseCallback(this->pimpl->window, &CallbackWindowClose);
	glfwSetCursorPosCallback(this->pimpl->window, &CallbackMousePos);
	glfwSetMouseButtonCallback(this->pimpl->window, &CallbackMouseButton);

	this->pimpl->valid = this->pimpl->vulkanInstance.create(this->pimpl->window);
}

auto Window::destroy() -> void
{
	if(this->valid())
	{
		glfwDestroyWindow(this->pimpl->window);
	}

	glfwTerminate();
}

auto Window::valid() noexcept -> bool
{
	return this->pimpl->valid;
}

auto Window::frame() -> void
{
	for(auto event : this->pimpl->events)
	{
		std::visit(EventHandler{[](auto) {}, this->pimpl->handleEventWindow, this->pimpl->handleEventMouse}, event);
	}

	this->pimpl->events.clear();

	glfwSwapBuffers(this->pimpl->window);
	glfwPollEvents();
}
