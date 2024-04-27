#include <aspire/widget/Window.h>
#include <gtest/gtest.h>

using aspire::widget::Widget;
using aspire::widget::Window;

TEST(Window, widget)
{
	Window window;

	auto widget = std::make_unique<Widget>();
	auto* w = widget.get();
	window.setWidget(std::move(widget));
	EXPECT_EQ(window.getWidget(), w);
}