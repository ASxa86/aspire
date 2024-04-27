#include <aspire/widget/Widget.h>

#include <aspire/core/PimplImpl.h>

using aspire::widget::Widget;

struct Widget::Impl
{
	int x{};
	int y{};
	int width{};
	int height{};
};

Widget::Widget() = default;
Widget::~Widget() = default;

auto Widget::setX(int x) noexcept -> void
{
	this->pimpl->x = x;
}

auto Widget::getX() const noexcept -> int
{
	return this->pimpl->x;
}

auto Widget::setY(int x) noexcept -> void
{
	this->pimpl->y = x;
}

auto Widget::getY() const noexcept -> int
{
	return this->pimpl->y;
}

auto Widget::setHeight(int x) noexcept -> void
{
	this->pimpl->height = x;
}

auto Widget::getHeight() const noexcept -> int
{
	return this->pimpl->height;
}

auto Widget::setWidth(int x) noexcept -> void
{
	this->pimpl->width = x;
}

auto Widget::getWidth() const noexcept -> int
{
	return this->pimpl->width;
}
