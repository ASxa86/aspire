#include <aspire/gui/EventMouse.h>

using aspire::EventMouse;

EventMouse::EventMouse(Type x) : Event{x}
{
}

auto EventMouse::setPosition(const Point& x) noexcept -> void
{
	this->position = x;
}

auto EventMouse::getPosition() const noexcept -> const Point&
{
	return this->position;
}

auto EventMouse::setButton(Button x) noexcept -> void
{
	this->button = x;
}

auto EventMouse::getButton() const noexcept -> Button
{
	return this->button;
}
