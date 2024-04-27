#include <aspire/widget/Widget.h>
#include <gtest/gtest.h>

using aspire::widget::Widget;

TEST(Widget, x)
{
	Widget widget;
	widget.setX(std::numeric_limits<int>::max());
	EXPECT_EQ(widget.getX(), std::numeric_limits<int>::max());
}

TEST(Widget, y)
{
	Widget widget;
	widget.setY(std::numeric_limits<int>::max());
	EXPECT_EQ(widget.getY(), std::numeric_limits<int>::max());
}

TEST(Widget, width)
{
	Widget widget;
	widget.setWidth(std::numeric_limits<int>::max());
	EXPECT_EQ(widget.getWidth(), std::numeric_limits<int>::max());
}

TEST(Widget, height)
{
	Widget widget;
	widget.setHeight(std::numeric_limits<int>::max());
	EXPECT_EQ(widget.getHeight(), std::numeric_limits<int>::max());
}