#include <aspire/render/Window.h>

#include <aspire/core/PimplImpl.h>
#include <vulkan/vulkan.h>

#include <GLFW/glfw3.h>

using aspire::render::Window;

struct Window::Impl
{
	GLFWwindow* window{};
	VkInstance instance{};
	VkSurfaceKHR surface{};

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

	this->pimpl->valid = this->pimpl->window != nullptr;
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
	glfwPollEvents();

	glfwSwapBuffers(this->pimpl->window);
}
