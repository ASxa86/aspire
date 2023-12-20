#include <aspire/gui/Window.h>

using aspire::Window;

auto Window::setTitle(std::string_view x) -> void
{
	this->title = x;
}

auto Window::getTitle() const noexcept -> std::string_view
{
	return this->title;
}

auto Window::setX(int x) noexcept -> void
{
	this->geometry[0] = x;
}

auto Window::getX() const noexcept -> int
{
	return this->geometry[0];
}

auto Window::setY(int x) noexcept -> void
{
	this->geometry[1] = x;
}

auto Window::getY() const noexcept -> int
{
	return this->geometry[1];
}

auto Window::setWidth(int x) noexcept -> void
{
	this->geometry[2] = x;
}

auto Window::getWidth() const noexcept -> int
{
	return this->geometry[2];
}

auto Window::setHeight(int x) noexcept -> void
{
	this->geometry[3] = x;
}

auto Window::getHeight() const noexcept -> int
{
	return this->geometry[3];
}

auto Window::setSurface(const Surface& x) -> void
{
	this->surface = x;
}

auto Window::getSurface() const -> const Surface&
{
	return this->surface;
}
