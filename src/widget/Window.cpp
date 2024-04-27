#include <aspire/widget/Window.h>

using aspire::widget::Window;

auto Window::setWidget(std::unique_ptr<Widget> x) -> void
{
	this->widget = std::move(x);
}

auto Window::getWidget() const -> Widget*
{
	return this->widget.get();
}