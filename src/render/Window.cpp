#include <aspire/render/Window.h>

#include <vulkan/vulkan.h>
#include <aspire/core/PimplImpl.h>

#include <GLFW/glfw3.h>

using aspire::render::Window;

struct Window::Impl
{
	Impl(const Traits& x) : traits{x}
	{
	}

	Traits traits;
	GLFWwindow* window{};
	VkInstance instance{};
	VkSurfaceKHR surface{};
};

Window::Window(const Traits& x) : pimpl{x}
{
	if(glfwVulkanSupported() == GLFW_FALSE)
	{
		return;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	this->pimpl->window =
		glfwCreateWindow(this->pimpl->traits.width, this->pimpl->traits.height, this->pimpl->traits.title.c_str(), nullptr, nullptr);

	glfwCreateWindowSurface(this->pimpl->instance, this->pimpl->window, nullptr, &this->pimpl->surface);
}

auto Window::move(int x, int y) -> void
{
	this->pimpl->traits.x = x;
	this->pimpl->traits.y = y;
	glfwSetWindowPos(this->pimpl->window, x, y);
}

auto Window::resize(int width, int height) -> void
{
	this->pimpl->traits.width = width;
	this->pimpl->traits.height = height;
	glfwSetWindowSize(this->pimpl->window, width, height);
}

auto Window::frame() -> void
{
}
