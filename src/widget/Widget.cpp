#include <aspire/widget/Widget.h>

#include <aspire/core/PimplImpl.h>

using aspire::widget::Widget;

struct Widget::Impl
{
	std::vector<Widget*> childWidgets;

	int x{};
	int y{};
	int width{};
	int height{};
};

Widget::Widget() : Object{}
{
	this->childAdded.connect(
		[this](auto* x)
		{
			auto* widget = dynamic_cast<Widget*>(x);

			if(widget == nullptr)
			{
				return;
			}

			this->pimpl->childWidgets.emplace_back(widget);
		});

	this->childRemoved.connect([this](auto* x) { std::erase(this->pimpl->childWidgets, x); });
}

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

auto Widget::childWidgets() const noexcept -> std::vector<Widget*>
{
	return this->pimpl->childWidgets;
}

auto Widget::update(aspire::scene::Node* /*unused*/) -> std::unique_ptr<aspire::scene::Node>
{
	return nullptr;
}
